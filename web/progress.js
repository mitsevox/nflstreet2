let sections=[];
const canvas=document.querySelector('#canvas');
function color(item) {
  if (item.matched === item.size) return 'var(--done)';
  if (!item.matched) return 'var(--empty)';
  const blend = Math.min(item.matched / item.size / 0.99, 1) * 100;
  return `color-mix(in srgb, var(--empty), var(--warm) ${blend}%)`;
}
// Balanced area partitioning keeps byte proportions exact across viewport sizes.
function partition(items,x,y,w,h,out){if(!items.length)return;if(items.length===1){out.push({...items[0],x,y,w,h});return;}let total=items.reduce((s,a)=>s+a.size,0),sum=0,split=1;for(let i=0;i<items.length-1;i++){sum+=items[i].size;split=i+1;if(sum>=total/2)break;}const ratio=sum/total;if(w>=h){partition(items.slice(0,split),x,y,w*ratio,h,out);partition(items.slice(split),x+w*ratio,y,w*(1-ratio),h,out);}else{partition(items.slice(0,split),x,y,w,h*ratio,out);partition(items.slice(split),x,y+h*ratio,w,h*(1-ratio),out);}}
const tooltip = document.querySelector('#map-tooltip');
const back = document.querySelector('#map-back');
const search = document.querySelector('#map-search');
const kindPicker = document.querySelector('#map-kind');
const motionPreference = window.matchMedia('(prefers-reduced-motion: reduce)');
const countAnimations = new WeakMap();
let mapFrame = null;
let activePulses = [];
let rippleSurface = null;
let boundaryGraph = [];
let mapLayout = [];
let hoverTarget = null;
let hoverItem = null;
function countUp(element, value, decimals = 0, suffix = '') {
  const previous = countAnimations.get(element);
  if (previous) cancelAnimationFrame(previous);
  const format = number => decimals ? number.toFixed(decimals) + suffix : Math.round(number).toLocaleString() + suffix;
  if (motionPreference.matches) {
    element.textContent = format(value);
    return;
  }
  const start = performance.now();
  const step = now => {
    const t = motionPreference.matches ? 1 : Math.min((now - start) / 780, 1);
    element.textContent = format(value * (1 - Math.pow(1 - t, 3)));
    if (t < 1) countAnimations.set(element, requestAnimationFrame(step));
    else countAnimations.delete(element);
  };
  element.textContent = format(0);
  countAnimations.set(element, requestAnimationFrame(step));
}
function fillTo(element, percent) {
  if (motionPreference.matches) element.style.width = percent + '%';
  else requestAnimationFrame(() => requestAnimationFrame(() => { element.style.width = percent + '%'; }));
}
function clearMapMotion() {
  if (mapFrame !== null) cancelAnimationFrame(mapFrame);
  mapFrame = null;
  activePulses = [];
  canvas.dataset.activePulses = '0';
  if (rippleSurface) {
    const context = rippleSurface.getContext('2d');
    context.clearRect(0, 0, rippleSurface.width, rippleSurface.height);
  }
}
motionPreference.addEventListener('change', () => {
  if (motionPreference.matches) clearMapMotion();
});
function clickOrigin(event, block) {
  const map = canvas.getBoundingClientRect();
  const target = block.getBoundingClientRect();
  const x = event?.detail ? event.clientX : target.left + target.width / 2;
  const y = event?.detail ? event.clientY : target.top + target.height / 2;
  return {x: Math.max(0, Math.min(map.width, x - map.left)),
    y: Math.max(0, Math.min(map.height, y - map.top))};
}
function makeBoundaryGraph(layout) {
  const nodes = [], byPoint = new Map(), rows = new Map(), columns = new Map();
  function group(groups, coordinate) {
    if (!groups.has(coordinate)) groups.set(coordinate, {nodes: [], spans: []});
    return groups.get(coordinate);
  }
  function point(x, y) {
    x = Math.round(x * 10) / 10;
    y = Math.round(y * 10) / 10;
    const key = x + ':' + y;
    if (!byPoint.has(key)) {
      const node = {x, y, edges: []};
      byPoint.set(key, nodes.length);
      nodes.push(node);
      group(rows, y).nodes.push(node);
      group(columns, x).nodes.push(node);
    }
    return nodes[byPoint.get(key)];
  }
  for (const item of layout) {
    const a = point(item.x, item.y), b = point(item.x + item.w, item.y);
    const c = point(item.x, item.y + item.h), d = point(item.x + item.w, item.y + item.h);
    group(rows, a.y).spans.push([a.x, b.x]);
    group(rows, c.y).spans.push([c.x, d.x]);
    group(columns, a.x).spans.push([a.y, c.y]);
    group(columns, b.x).spans.push([b.y, d.y]);
  }
  function connect(groups, axis) {
    for (const entry of groups.values()) {
      entry.nodes.sort((a, b) => a[axis] - b[axis]);
      entry.spans.sort((a, b) => a[0] - b[0]);
      let span = 0, end = -Infinity;
      for (let i = 0; i < entry.nodes.length - 1; i++) {
        const a = entry.nodes[i], b = entry.nodes[i + 1];
        while (span < entry.spans.length && entry.spans[span][0] <= a[axis] + 0.1) {
          end = Math.max(end, entry.spans[span++][1]);
        }
        const length = b[axis] - a[axis];
        if (length > 0 && end >= b[axis] - 0.1) {
          a.edges.push({node: b, length});
          b.edges.push({node: a, length});
        }
      }
    }
  }
  connect(rows, 'x');
  connect(columns, 'y');
  return nodes;
}
function drawPulses(now) {
  mapFrame = null;
  if (!rippleSurface) return;
  const context = rippleSurface.getContext('2d');
  const width = canvas.clientWidth, height = canvas.clientHeight;
  const ratio = rippleSurface.width / width;
  context.setTransform(ratio, 0, 0, ratio, 0, 0);
  context.globalCompositeOperation = 'source-over';
  context.clearRect(0, 0, width, height);
  activePulses = activePulses.filter(pulse => now - pulse.start < pulse.duration);
  canvas.dataset.activePulses = activePulses.length;
  if (!activePulses.length) return;
  context.fillStyle = getComputedStyle(document.documentElement).getPropertyValue('--bg').trim();
  context.fillRect(0, 0, width, height);
  context.globalCompositeOperation = 'lighten';
  context.lineWidth = 1.5;
  context.lineCap = 'butt';
  for (const pulse of activePulses) pulse.paint(context, now - pulse.start);
  context.globalCompositeOperation = 'source-over';
  mapFrame = requestAnimationFrame(drawPulses);
}
function ripple(origin, start = performance.now()) {
  if (!origin || motionPreference.matches || !rippleSurface || !boundaryGraph.length) return;
  const width = canvas.clientWidth, height = canvas.clientHeight;
  let seed = boundaryGraph[0], nearest = Infinity;
  for (const node of boundaryGraph) {
    const distance = Math.hypot(node.x - origin.x, node.y - origin.y);
    if (distance < nearest) { seed = node; nearest = distance; }
  }
  // Walk connected seams; branch arrivals depend on their route, rather than a circular front.
  const frontier = [], costs = new Map([[seed, 0]]), parents = new Map(), visited = new Set();
  function push(entry) {
    frontier.push(entry);
    let index = frontier.length - 1;
    while (index) {
      const parent = (index - 1) >> 1;
      if (frontier[parent].cost <= entry.cost) break;
      frontier[index] = frontier[parent];
      index = parent;
    }
    frontier[index] = entry;
  }
  function pop() {
    const first = frontier[0], last = frontier.pop();
    if (!frontier.length) return first;
    let index = 0;
    while (index * 2 + 1 < frontier.length) {
      let child = index * 2 + 1;
      if (child + 1 < frontier.length && frontier[child + 1].cost < frontier[child].cost) child++;
      if (frontier[child].cost >= last.cost) break;
      frontier[index] = frontier[child];
      index = child;
    }
    frontier[index] = last;
    return first;
  }
  const routeCount = 16;
  const reach = 1500;
  const easingDistance = 520;
  const pace = 1.8, initialPace = 0.22;
  const arrivalAt = cost => pace * (initialPace * cost + (1 - initialPace) * cost * cost / (2 * easingDistance));
  const distanceAt = time => {
    const clock = Math.max(0, time) / pace;
    return 2 * clock / (initialPace + Math.sqrt(initialPace * initialPace + 2 * (1 - initialPace) * clock / easingDistance));
  };
  const endpoints = Array(routeCount).fill(null);
  push({node: seed, cost: 0});
  while (frontier.length && visited.size < 18000) {
    const current = pop();
    if (visited.has(current.node)) continue;
    visited.add(current.node);
    const dx = current.node.x - seed.x, dy = current.node.y - seed.y;
    const distance = Math.hypot(dx, dy);
    const sector = Math.floor((Math.atan2(dy, dx) + Math.PI) / (Math.PI * 2) * routeCount) % routeCount;
    if (distance > (endpoints[sector]?.distance ?? 0)) endpoints[sector] = {...current, distance};
    for (const edge of current.node.edges) {
      const cost = current.cost + edge.length + 5;
      if (cost > reach || visited.has(edge.node) || cost >= (costs.get(edge.node) ?? Infinity)) continue;
      costs.set(edge.node, cost);
      parents.set(edge.node, {a: current.node, b: edge.node, from: current.cost, to: cost,
        arrival: arrivalAt(current.cost), travel: arrivalAt(cost) - arrivalAt(current.cost)});
      push({node: edge.node, cost});
    }
  }
  // Illuminate a few connected routes, rather than flooding every reachable seam.
  const selected = new Map();
  for (const endpoint of endpoints) {
    let node = endpoint?.node;
    while (node && node !== seed) {
      const edge = parents.get(node);
      if (!edge) break;
      selected.set(node, edge);
      node = edge.a;
    }
  }
  const traces = [...selected.values()].sort((a, b) => a.from - b.from);
  const outgoing = new Map();
  for (const trace of traces) {
    if (!outgoing.has(trace.a)) outgoing.set(trace.a, []);
    outgoing.get(trace.a).push(trace);
  }
  for (const branches of outgoing.values()) {
    branches.sort((a, b) => Math.atan2(a.b.y - a.a.y, a.b.x - a.a.x) - Math.atan2(b.b.y - b.a.y, b.b.x - b.a.x));
  }
  const clocks = new Map([[seed, {arrival: 0, pace: 1, lifetime: 950}]]);
  const branchPaces = [0.65, 1.35, 0.9, 1.7];
  const branchLifetimes = [520, 1150, 720, 1450];
  for (const trace of traces) {
    const parent = clocks.get(trace.a);
    const siblings = outgoing.get(trace.a);
    const rank = siblings.indexOf(trace);
    trace.pace = siblings.length > 1 ? parent.pace * 0.25 + branchPaces[rank % 4] * 0.75 : parent.pace;
    trace.lifetime = siblings.length > 1 ? parent.lifetime * 0.25 + branchLifetimes[rank % 4] * 0.75 : parent.lifetime;
    trace.arrival = parent.arrival;
    trace.travel = (arrivalAt(trace.to) - arrivalAt(trace.from)) * trace.pace;
    clocks.set(trace.b, {arrival: trace.arrival + trace.travel, pace: trace.pace, lifetime: trace.lifetime});
  }
  const attackTime = 45;
  const duration = Math.max(0, ...traces.map(trace => trace.arrival + trace.travel + trace.lifetime));
  const styles = getComputedStyle(document.documentElement);
  const background = styles.getPropertyValue('--bg').trim();
  const rgb = hex => [1, 3, 5].map(index => parseInt(hex.slice(index, index + 2), 16));
  const dark = rgb(background), light = rgb(styles.getPropertyValue('--accent').trim());
  function paint(context, elapsed) {
    for (const trace of traces) {
      const age = elapsed - trace.arrival;
      if (age <= 0 || age >= trace.travel + trace.lifetime) continue;
      const distance = distanceAt(arrivalAt(trace.from) + age / trace.pace);
      const progress = Math.max(0, Math.min((distance - trace.from) / (trace.to - trace.from), 1));
      const gradient = context.createLinearGradient(trace.a.x, trace.a.y, trace.b.x, trace.b.y);
      // Each point fades from its own arrival; routes continue beyond the visible glow.
      for (let step = 0; step <= 8; step++) {
        const position = step / 8;
        const cost = trace.from + (trace.to - trace.from) * position;
        const pointAge = age - (arrivalAt(cost) - arrivalAt(trace.from)) * trace.pace;
        const fade = Math.pow(Math.max(0, 1 - Math.max(0, pointAge - attackTime) / (trace.lifetime - attackTime)), 1.3);
        const brightness = Math.max(0, Math.min(pointAge / attackTime, 1)) * fade * Math.exp(-cost / 340);
        gradient.addColorStop(position, `rgb(${dark.map((value, index) => Math.round(value + (light[index] - value) * brightness)).join(',')})`);
      }
      context.strokeStyle = gradient;
      context.beginPath();
      context.moveTo(trace.a.x, trace.a.y);
      context.lineTo(trace.a.x + (trace.b.x - trace.a.x) * progress, trace.a.y + (trace.b.y - trace.a.y) * progress);
      context.stroke();
    }
  }
  activePulses.push({origin, start, duration, width, height, paint});
  canvas.dataset.activePulses = activePulses.length;
  if (mapFrame === null) mapFrame = requestAnimationFrame(drawPulses);
}
const path = [];
let mapKind = 'code';
function leaves(items) {
  return items.flatMap(item => item.children?.length ? leaves(item.children) : [item]);
}
function mapItems() {
  const roots = sections.filter(section => section.kind === mapKind);
  const query = search.value.trim().toLocaleLowerCase();
  if (query) return roots.flatMap(item => item.name.toLocaleLowerCase().includes(query)
    ? [item] : leaves([item]).filter(leaf => leaf.name.toLocaleLowerCase().includes(query))); 
  return path.at(-1)?.children || roots;
}
search.addEventListener('input', () => {
  path.length = 0;
  render('search');
});
kindPicker.querySelectorAll('button').forEach(button => {
  button.addEventListener('click', event => {
    mapKind = button.dataset.kind;
    kindPicker.dataset.selected = mapKind;
    kindPicker.querySelectorAll('button').forEach(option => option.setAttribute('aria-pressed', option === button));
    path.length = 0;
    render('switch', clickOrigin(event, button));
  });
});
let activeTile = null;
const percent = item => (item.matched / item.size * 100).toFixed(2) + '% matched';
function hideTooltip() {
  tooltip.hidden = true;
  activeTile?.removeAttribute('aria-describedby');
  activeTile = null;
}
function showTooltip(block, item, x, y) {
  showTooltipText(block, (item.source && item.source !== item.name ? item.source + ' · ' : '') + item.name + ' · ' + percent(item) + (item.source === item.name && item.complete === false ? ' · partial file' : ''), x, y);
}
function showTooltipText(block, text, x, y) {
  hideTooltip();
  activeTile = block;
  tooltip.textContent = text;
  tooltip.hidden = false;
  block.setAttribute('aria-describedby', 'map-tooltip');
  const gap = 12;
  tooltip.style.left = Math.max(8, Math.min(x + gap, window.innerWidth - tooltip.offsetWidth - 8)) + 'px';
  tooltip.style.top = Math.max(8, Math.min(y + gap, window.innerHeight - tooltip.offsetHeight - 8)) + 'px';
}
let palette = null;
function colorValue(item) {
  if (item.matched === item.size) return palette.done;
  if (!item.matched) return palette.empty;
  const fraction = Math.min(item.matched / item.size / 0.99, 1);
  return `rgb(${palette.emptyRGB.map((value, index) => Math.round(value + (palette.warmRGB[index] - value) * fraction)).join(',')})`;
}
function drawMap(layout) {
  const ratio = Math.min(window.devicePixelRatio || 1, 2);
  const scene = document.createElement('canvas');
  scene.className = 'map-pixels';
  scene.setAttribute('aria-hidden', 'true');
  scene.width = Math.round(canvas.clientWidth * ratio);
  scene.height = Math.round(canvas.clientHeight * ratio);
  rippleSurface = document.createElement('canvas');
  rippleSurface.className = 'map-ripple';
  rippleSurface.setAttribute('aria-hidden', 'true');
  rippleSurface.width = scene.width;
  rippleSurface.height = scene.height;
  const styles = getComputedStyle(document.documentElement);
  const rgb = hex => [1, 3, 5].map(index => parseInt(hex.slice(index, index + 2), 16));
  palette = {empty: styles.getPropertyValue('--empty').trim(), done: styles.getPropertyValue('--done').trim()};
  palette.emptyRGB = rgb(palette.empty);
  palette.warmRGB = rgb(styles.getPropertyValue('--warm').trim());
  const context = scene.getContext('2d');
  context.scale(ratio, ratio);
  // Transparent seams expose the ripple underneath; the opaque blocks are drawn only once.
  for (const item of layout) {
    context.fillStyle = colorValue(item);
    const inset = Math.min(0.6, item.w * 0.2, item.h * 0.2);
    context.fillRect(item.x + inset, item.y + inset, item.w - inset * 2, item.h - inset * 2);
  }
  boundaryGraph = makeBoundaryGraph(layout);
  canvas.append(rippleSurface, scene);
}
function selectItem(item, block, event) {
  const origin = clickOrigin(event, block);
  hideTooltip();
  if (item.children?.length) {
    path.push(item);
    render('enter', origin);
    back.focus();
  } else {
    const rect = block.getBoundingClientRect();
    showTooltip(block, item, rect.left, rect.top);
    ripple(origin);
  }
}
function hitItem(event) {
  const rect = canvas.getBoundingClientRect();
  const x = event.clientX - rect.left, y = event.clientY - rect.top;
  return mapLayout.find(item => x >= item.x && x < item.x + item.w && y >= item.y && y < item.y + item.h);
}
function targetItem(item) {
  hoverItem = item;
  if (!hoverTarget) {
    hoverTarget = document.createElement('button');
    hoverTarget.type = 'button';
    hoverTarget.className = 'tile map-hit';
    hoverTarget.addEventListener('click', event => {
      event.stopPropagation();
      selectItem(hoverItem, hoverTarget, event);
    });
    hoverTarget.addEventListener('blur', hideTooltip);
    hoverTarget.addEventListener('focus', () => {
      const rect = hoverTarget.getBoundingClientRect();
      showTooltip(hoverTarget, hoverItem, rect.left, rect.top);
    });
    canvas.append(hoverTarget);
  }
  hoverTarget.dataset.name = item.name;
  hoverTarget.dataset.mapIndex = mapLayout.indexOf(item);
  hoverTarget.setAttribute('aria-label', item.name + ' · ' + percent(item));
  Object.assign(hoverTarget.style, {left: item.x + 'px', top: item.y + 'px', width: item.w + 'px', height: item.h + 'px'});
  return hoverTarget;
}
canvas.addEventListener('pointermove', event => {
  if (event.pointerType === 'touch' || event.target.closest('.tile:not(.map-hit)')) return;
  const item = hitItem(event);
  if (item) showTooltip(targetItem(item), item, event.clientX, event.clientY);
});
canvas.addEventListener('keydown', event => {
  if (!['ArrowRight', 'ArrowDown', 'ArrowLeft', 'ArrowUp', 'Home', 'End'].includes(event.key)) return;
  event.preventDefault();
  const index = Number(event.target.dataset.mapIndex);
  const next = event.key === 'Home' ? 0 : event.key === 'End' ? mapLayout.length - 1 :
    Math.max(0, Math.min(mapLayout.length - 1, index + (['ArrowRight', 'ArrowDown'].includes(event.key) ? 1 : -1)));
  if (mapLayout[next]) {
    const target = targetItem(mapLayout[next]);
    target.focus();
    const rect = target.getBoundingClientRect();
    showTooltip(target, mapLayout[next], rect.left, rect.top);
  }
});
canvas.addEventListener('click', event => {
  if (event.target.closest('.tile:not(.map-hit)')) return;
  const item = hitItem(event);
  if (item) selectItem(item, targetItem(item), event);
});
canvas.addEventListener('pointerleave', () => {
  hideTooltip();
  if (hoverTarget !== document.activeElement) {
    hoverTarget?.remove();
    hoverTarget = null;
  }
});
function render(direction = null, origin = null) {
  if (!sections.length) return;
  const continuing = activePulses.filter(pulse => performance.now() - pulse.start < pulse.duration)
    .map(pulse => ({origin: {x: pulse.origin.x / pulse.width * canvas.clientWidth,
      y: pulse.origin.y / pulse.height * canvas.clientHeight}, start: pulse.start}));
  clearMapMotion();
  const focusedIndex = !direction && canvas.contains(document.activeElement) ? Number(document.activeElement.dataset.mapIndex) : null;
  hideTooltip();
  const current = path.at(-1);
  const items = mapItems();
  back.hidden = !current;
  canvas.setAttribute('aria-description', 'Use arrow keys to move between blocks, Home or End to reach the first or last block, and Enter to select.');
  canvas.setAttribute('aria-label', current ? current.name + ' contents' : (mapKind === 'code' ? 'Code' : 'Data') + ' section map');
  const layout = [];
  partition([...items].sort((a, b) => b.size - a.size), 0, 0, canvas.clientWidth, canvas.clientHeight, layout);
  canvas.replaceChildren();
  hoverTarget = null;
  rippleSurface = null;
  mapLayout = layout;
  if (!items.length) {
    const empty = document.createElement('div');
    empty.className = 'empty-search';
    empty.textContent = 'No matches';
    canvas.append(empty);
    return;
  }
  drawMap(layout);
  // Pixel drawing keeps dense maps fast; larger cells and search results retain native keyboard targets.
  const targets = search.value.trim() ? layout.slice(0, 128) : layout.slice(0, 64);
  for (const [index, item] of targets.entries()) {
    const block = document.createElement('button');
    block.type = 'button';
    block.className = 'tile';
    block.dataset.name = item.name;
    block.dataset.mapIndex = index;
    Object.assign(block.style, {left: item.x + 'px', top: item.y + 'px', width: item.w + 'px', height: item.h + 'px'});
    block.setAttribute('aria-label', item.name + ' · ' + percent(item));
    block.addEventListener('pointerenter', event => {
      if (event.pointerType !== 'touch') showTooltip(block, item, event.clientX, event.clientY);
    });
    block.addEventListener('pointermove', event => {
      if (event.pointerType !== 'touch') showTooltip(block, item, event.clientX, event.clientY);
    });
    block.addEventListener('pointerleave', hideTooltip);
    block.addEventListener('blur', hideTooltip);
    block.addEventListener('focus', () => {
      const rect = block.getBoundingClientRect();
      showTooltip(block, item, rect.left, rect.top);
    });
    block.addEventListener('click', event => selectItem(item, block, event));
    canvas.append(block);
    if (index === focusedIndex) block.focus();
  }
  if (focusedIndex !== null && focusedIndex >= targets.length && layout[focusedIndex]) targetItem(layout[focusedIndex]).focus();
  for (const pulse of continuing) ripple(pulse.origin, pulse.start);
  if (direction !== 'search') ripple(origin);
}
back.addEventListener('click', event => {
  const origin = clickOrigin(event, back);
  const previous = path.pop();
  render('back', origin);
  const tile = [...canvas.children].find(block => block.dataset.name === previous?.name);
  tile?.focus();
});
document.addEventListener('keydown', event => {
  if (event.key === 'Escape') hideTooltip();
});
window.addEventListener('scroll', hideTooltip, {passive: true});
function validMap(items, kind = null) {
  return Array.isArray(items) && items.length > 0 && items.every(item => {
    if (!['code', 'data'].includes(item.kind) || (kind && item.kind !== kind) ||
        typeof item.name !== 'string' || !validMeasure({total: item.size, linked: item.linked, matched: item.matched})) return false;
    if (item.children) {
      if (!validMap(item.children, item.kind)) return false;
      for (const field of ['size', 'linked', 'matched']) {
        if (item.children.reduce((sum, child) => sum + child[field], 0) !== item[field]) return false;
      }
    }
    return true;
  });
}
function renderFunctions(functions) {
  const available = functions && functions.basis !== 'unavailable';
  if (available && (functions.basis !== 'provisional-analysis' || !Number.isSafeInteger(functions.total) || functions.total <= 0 ||
      !['exact', 'named'].every(field => Number.isSafeInteger(functions[field]) && functions[field] >= 0 && functions[field] <= functions.total))) {
    throw new Error('Invalid function progress');
  }
  for (const field of ['exact', 'named']) {
    const stat = document.querySelector('[data-function="' + field + '"]');
    const value = available ? functions[field] / functions.total * 100 : 0;
    if (available) countUp(stat.querySelector('strong'), functions[field]);
    else stat.querySelector('strong').textContent = '—';
    stat.querySelector('.function-total span').textContent = available ? functions.total.toLocaleString() : '—';
    if (available) countUp(stat.querySelector('.function-percent'), value, 2, '%');
    else stat.querySelector('.function-percent').textContent = '—';
    const track = stat.querySelector('.function-track');
    fillTo(track.firstElementChild, value);
    if (available) {
      track.setAttribute('aria-valuenow', value);
      track.removeAttribute('aria-valuetext');
    } else {
      track.removeAttribute('aria-valuenow');
      track.setAttribute('aria-valuetext', 'Unavailable');
    }
  }
}

function validMeasure(m){return m&&Number.isSafeInteger(m.total)&&m.total>0&&Number.isSafeInteger(m.linked)&&m.linked>=0&&m.linked<=m.total&&Number.isSafeInteger(m.matched)&&m.matched>=0&&m.matched<=m.linked;}
async function loadProgress(){try{const response=await fetch('./progress.json',{cache:'no-cache'});if(!response.ok)throw new Error('Progress unavailable');const data=await response.json();if(data.schema!==1||data.target!=='GN7E69'||data.basis!=='executable-sections'||data.baseline!=='verified'||!(/^[a-f0-9]{40}$/).test(data.revision)||!validMeasure(data.measures?.code)||!validMeasure(data.measures?.data)||!Array.isArray(data.sections)||!data.sections.length)throw new Error('Invalid progress');for(const item of data.sections){if(!['code','data'].includes(item.kind)||typeof item.name!=='string'||!/^0x[0-9A-F]{8}$/.test(item.address)||!validMeasure({total:item.size,linked:item.linked,matched:item.matched}))throw new Error('Invalid section');}for(const kind of ['code','data']){for(const field of ['total','linked','matched']){const sum=data.sections.filter(s=>s.kind===kind).reduce((n,s)=>n+s[field==='total'?'size':field],0);if(sum!==data.measures[kind][field])throw new Error('Inconsistent progress');}}
const files=data.files || data.sections;
if(!validMap(data.sections)||!validMap(files))throw new Error('Invalid map');
for(const kind of ['code','data']){for(const field of ['total','linked','matched']){
  if(files.filter(item=>item.kind===kind).reduce((sum,item)=>sum+item[field==='total'?'size':field],0)!==data.measures[kind][field])throw new Error('Inconsistent file map');
}}
renderFunctions(data.functions);sections=files;document.querySelectorAll('.progress-element').forEach(element => {
  const kind = element.dataset.progress;
  const measures = data.measures[kind];
  const linked = measures.linked / measures.total * 100;
  const matched = measures.matched / measures.total * 100;
  const track = element.querySelector('.track');
  const description = `${kind === 'code' ? 'Code' : 'Data'} · Linked ${linked.toFixed(2)}% · Matched ${matched.toFixed(2)}%`;
  countUp(element.querySelector('.progress-value'), matched, 2, '%');
  track.setAttribute('aria-valuenow', matched);
  track.setAttribute('aria-valuetext', `Linked ${linked.toFixed(2)}%, matched ${matched.toFixed(2)}%`);
  fillTo(track.querySelector('.progress-linked'), linked);
  fillTo(track.querySelector('.progress-matched'), matched);
  element.addEventListener('pointerenter', event => {
    if (event.pointerType !== 'touch') showTooltipText(track, description, event.clientX, event.clientY);
  });
  element.addEventListener('pointermove', event => {
    if (event.pointerType !== 'touch') showTooltipText(track, description, event.clientX, event.clientY);
  });
  element.addEventListener('pointerleave', hideTooltip);
  track.addEventListener('focus', () => {
    const rect = track.getBoundingClientRect();
    showTooltipText(track, description, rect.left, rect.bottom);
  });
  track.addEventListener('blur', hideTooltip);
  track.addEventListener('click', () => {
    const rect = track.getBoundingClientRect();
    showTooltipText(track, description, rect.left, rect.bottom);
  });
});const link=document.querySelector('#build-link');link.href='https://github.com/mitsevox/nflstreet2/commit/'+data.revision;link.textContent='Baseline verified · '+data.revision.slice(0,7);link.title='Built '+data.built_at;render();}catch(error){renderFunctions(null);document.querySelector('#build-link').textContent='Progress unavailable';canvas.textContent='Progress unavailable';document.querySelectorAll('.track').forEach(track=>track.setAttribute('aria-valuetext','Unavailable'));}}
new ResizeObserver(() => render()).observe(canvas);loadProgress();
