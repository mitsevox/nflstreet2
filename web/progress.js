let sections=[];
const canvas=document.querySelector('#canvas');
function color(item){return item.matched===item.size?'var(--done)':item.matched>0?'var(--warm)':'var(--empty)'}
// Balanced area partitioning keeps byte proportions exact across viewport sizes.
function partition(items,x,y,w,h,out){if(!items.length)return;if(items.length===1){out.push({...items[0],x,y,w,h});return;}let total=items.reduce((s,a)=>s+a.size,0),sum=0,split=1;for(let i=0;i<items.length-1;i++){sum+=items[i].size;split=i+1;if(sum>=total/2)break;}const ratio=sum/total;if(w>=h){partition(items.slice(0,split),x,y,w*ratio,h,out);partition(items.slice(split),x+w*ratio,y,w*(1-ratio),h,out);}else{partition(items.slice(0,split),x,y,w,h*ratio,out);partition(items.slice(split),x,y+h*ratio,w,h*(1-ratio),out);}}
const tooltip = document.querySelector('#map-tooltip');
const back = document.querySelector('#map-back');
const path = [];
let activeTile = null;
const percent = item => (item.matched / item.size * 100).toFixed(2) + '% matched';
function hideTooltip() {
  tooltip.hidden = true;
  activeTile?.removeAttribute('aria-describedby');
  activeTile = null;
}
function showTooltip(block, item, x, y) {
  hideTooltip();
  activeTile = block;
  tooltip.textContent = item.name + ' · ' + percent(item);
  tooltip.hidden = false;
  block.setAttribute('aria-describedby', 'map-tooltip');
  const gap = 12;
  tooltip.style.left = Math.max(8, Math.min(x + gap, window.innerWidth - tooltip.offsetWidth - 8)) + 'px';
  tooltip.style.top = Math.max(8, Math.min(y + gap, window.innerHeight - tooltip.offsetHeight - 8)) + 'px';
}
function render() {
  if (!sections.length) return;
  const focusedName = canvas.contains(document.activeElement) ? document.activeElement.dataset.name : null;
  hideTooltip();
  const current = path.at(-1);
  const items = current ? current.children : sections.filter(section => section.kind === 'code');
  back.hidden = !current;
  canvas.setAttribute('aria-label', current ? current.name + ' contents' : 'Code section map');
  const layout = [];
  partition([...items].sort((a, b) => b.size - a.size), 0, 0, canvas.clientWidth, canvas.clientHeight, layout);
  canvas.replaceChildren();
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
        render();
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
}
back.addEventListener('click', () => {
  const previous = path.pop();
  render();
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
    stat.querySelector('strong').textContent = available ? functions[field].toLocaleString() : '—';
    stat.querySelector('.function-total span').textContent = available ? functions.total.toLocaleString() : '—';
    stat.querySelector('.function-percent').textContent = available ? value.toFixed(2) + '%' : '—';
    const track = stat.querySelector('.function-track');
    track.firstElementChild.style.width = value + '%';
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
if(!validMap(data.sections))throw new Error('Invalid map');renderFunctions(data.functions);sections=data.sections;document.querySelectorAll('.progress-element').forEach((element,index)=>{const kind=index===0?'code':'data';const measures=data.measures[kind];element.title='Source-object bytes relative to executable section sizes; original objects do not count as source progress.';element.querySelectorAll('.track').forEach((track,row)=>{const field=row===0?'linked':'matched';const percent=measures[field]/measures.total*100;track.setAttribute('aria-valuenow',percent);track.removeAttribute('aria-valuetext');track.firstElementChild.style.width=percent+'%';track.previousElementSibling.lastElementChild.textContent=percent.toFixed(2)+'%';});});const link=document.querySelector('#build-link');link.href='https://github.com/mitsevox/nflstreet2/commit/'+data.revision;link.textContent='Baseline verified · '+data.revision.slice(0,7);link.title='Built '+data.built_at;render();}catch(error){renderFunctions(null);document.querySelector('#build-link').textContent='Progress unavailable';canvas.textContent='Progress unavailable';document.querySelectorAll('.track').forEach(track=>track.setAttribute('aria-valuetext','Unavailable'));}}
new ResizeObserver(render).observe(canvas);loadProgress();
