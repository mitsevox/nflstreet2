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
let mapAnimation = null;
let lineOverlay = null;
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
  mapAnimation?.cancel();
  mapAnimation = null;
  lineOverlay?.remove();
  lineOverlay = null;
}
motionPreference.addEventListener('change', () => {
  if (motionPreference.matches) clearMapMotion();
});
function animateMap(layout, direction, origin) {
  if (!direction || motionPreference.matches || !layout.length) return;
  // One surface fade and at most 48 decorative paths, even for a 14,000-function map.
  mapAnimation = canvas.animate([{opacity: 0.6}, {opacity: 1}], {
    duration: direction === 'search' ? 180 : 360, easing: 'cubic-bezier(.22,1,.36,1)'
  });
  if (direction === 'search') return;
  const svg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
  svg.classList.add('map-lines');
  svg.setAttribute('aria-hidden', 'true');
  svg.setAttribute('viewBox', `0 0 ${canvas.clientWidth} ${canvas.clientHeight}`);
  svg.setAttribute('preserveAspectRatio', 'none');
  svg.style.transformOrigin = origin || '50% 50%';
  svg.style.setProperty('--line-scale', direction === 'back' ? '0.975' : '1.025');
  for (const [index, item] of layout.filter(item => item.w >= 3 && item.h >= 3).slice(0, 48).entries()) {
    const line = document.createElementNS('http://www.w3.org/2000/svg', 'path');
    line.setAttribute('d', `M${item.x},${item.y}h${item.w}v${item.h}h${-item.w}Z`);
    line.setAttribute('pathLength', '1');
    line.style.animationDelay = Math.min(index * 7, 180) + 'ms';
    svg.append(line);
  }
  lineOverlay = svg;
  canvas.parentElement.append(svg);
  svg.addEventListener('animationend', event => {
    if (event.target === svg) {
      svg.remove();
      if (lineOverlay === svg) lineOverlay = null;
    }
  });
}
const path = [];
let mapKind = 'code';
function leaves(items) {
  return items.flatMap(item => item.children?.length ? leaves(item.children) : [item]);
}
function mapItems() {
  const roots = sections.filter(section => section.kind === mapKind);
  const query = search.value.trim().toLocaleLowerCase();
  if (query) return leaves(roots).filter(item => item.name.toLocaleLowerCase().includes(query));
  return path.at(-1)?.children || roots;
}
search.addEventListener('input', () => {
  path.length = 0;
  render('search');
});
kindPicker.querySelectorAll('button').forEach(button => {
  button.addEventListener('click', () => {
    mapKind = button.dataset.kind;
    kindPicker.dataset.selected = mapKind;
    kindPicker.querySelectorAll('button').forEach(option => option.setAttribute('aria-pressed', option === button));
    path.length = 0;
    render('switch');
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
  showTooltipText(block, item.name + ' · ' + percent(item), x, y);
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
function render(direction = null, origin = null) {
  if (!sections.length) return;
  clearMapMotion();
  const focusedName = canvas.contains(document.activeElement) ? document.activeElement.dataset.name : null;
  hideTooltip();
  const current = path.at(-1);
  const items = mapItems();
  back.hidden = !current;
  canvas.setAttribute('aria-label', current ? current.name + ' contents' : (mapKind === 'code' ? 'Code' : 'Data') + ' section map');
  const layout = [];
  partition([...items].sort((a, b) => b.size - a.size), 0, 0, canvas.clientWidth, canvas.clientHeight, layout);
  canvas.replaceChildren();
  if (!items.length) {
    const empty = document.createElement('div');
    empty.className = 'empty-search';
    empty.textContent = 'No matches';
    canvas.append(empty);
    return;
  }
  for (const item of layout) {
    const block = document.createElement('button');
    block.type = 'button';
    block.className = 'tile';
    block.dataset.name = item.name;
    Object.assign(block.style, {left: item.x + 'px', top: item.y + 'px', width: item.w + 'px', height: item.h + 'px', background: color(item)});
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
    const select = () => {
      hideTooltip();
      if (item.children?.length) {
        path.push(item);
        render('enter', `${item.x + item.w / 2}px ${item.y + item.h / 2}px`);
        back.focus();
      } else {
        const rect = block.getBoundingClientRect();
        showTooltip(block, item, rect.left, rect.top);
      }
    };
    block.addEventListener('click', select);
    canvas.append(block);
    if (item.name === focusedName) block.focus();
  }
  animateMap(layout, direction, origin);
}
back.addEventListener('click', () => {
  const previous = path.pop();
  render('back');
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
if(!validMap(data.sections))throw new Error('Invalid map');renderFunctions(data.functions);sections=data.sections;document.querySelectorAll('.progress-element').forEach(element => {
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
