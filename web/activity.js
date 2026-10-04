(() => {
  const chart=document.querySelector('.history-chart'),scrub=document.querySelector('#history-scrub');
  const list=document.querySelector('.contributor-rankings');
  const fields=['code','data'];
  const shortDate=new Intl.DateTimeFormat(undefined,{month:'short',day:'numeric'});
  const fullDate=new Intl.DateTimeFormat(undefined,{month:'short',day:'numeric',hour:'numeric',minute:'2-digit'});
  let rows=[],index=0,ceiling=10;
  const percent=(row,kind)=>row[kind].linked/row[kind].total*100;
  let first=0,last=1;
  const x=i=>10+(rows.length===1?1:(Date.parse(rows[i].built_at)-first)/(last-first))*980;
  const y=value=>200-value/ceiling*180;
  function draw(){
    for(const kind of fields){
      const values=rows.map(row=>percent(row,kind));
      document.querySelector(`[data-line="${kind}"]`).setAttribute('d',values.map((v,i)=>(i?'L':'M')+x(i)+','+y(v)).join(' '));
      const dot=document.querySelector(`[data-dot="${kind}"]`);dot.setAttribute('cx',x(index));dot.setAttribute('cy',y(values[index]));
      document.querySelector(`[data-history-value="${kind}"]`).textContent=values[index].toFixed(2)+'%';
    }
    const cursor=document.querySelector('#history-cursor');cursor.setAttribute('x1',x(index));cursor.setAttribute('x2',x(index));
    const time=document.querySelector('#history-date');time.textContent=fullDate.format(new Date(rows[index].built_at));time.dateTime=rows[index].built_at;
    scrub.value=index;scrub.setAttribute('aria-valuetext',fullDate.format(new Date(rows[index].built_at))+': code '+percent(rows[index],'code').toFixed(2)+'% linked, data '+percent(rows[index],'data').toFixed(2)+'% linked');
  }
  function renderPeople(people){
    list.replaceChildren();
    people.forEach((person,i)=>{
      const row=document.createElement('li'),place=document.createElement('span');place.className='contributor-place';place.textContent=String(i+1).padStart(2,'0');
      if(i<3){const medal=document.createElement('span');medal.className='rank-medal';medal.setAttribute('aria-hidden','true');medal.textContent=['🥇','🥈','🥉'][i];place.append(medal);}
      const avatar=document.createElement('span');avatar.className='person-avatar avatar-'+['one','two','three','four'][i%4];avatar.setAttribute('aria-hidden','true');avatar.textContent=person.login.slice(0,2).toUpperCase();
      const image=document.createElement('img');image.src='https://avatars.githubusercontent.com/u/'+person.id+'?s=80';image.alt='';image.width=40;image.height=40;image.loading='lazy';image.referrerPolicy='no-referrer';image.addEventListener('error',()=>image.remove());avatar.append(image);
      const name=document.createElement('a');name.href='https://github.com/'+person.login;name.className='contributor-name';name.textContent=person.login;
      const count=document.createElement('span');count.className='contributor-functions';const value=document.createElement('b');value.textContent=person.functions.toLocaleString();count.append(value,document.createTextNode(person.functions===1?' function':' functions'));
      row.append(place,avatar,name,count);list.append(row);
    });
  }
  function validate(data){
    if(data.schema!==1||data.target!=='GN7E69'||data.target_sha1!=='3561e946e9ff785b68692f87d2ba85d81fd2dcf4'||!Array.isArray(data.snapshots)||!data.snapshots.length||!Array.isArray(data.contributors))throw Error('Invalid project activity');
    const seen=new Set();let previous=-Infinity;
    for(const row of data.snapshots){
      const time=Date.parse(row.built_at);
      if(!/^[a-f0-9]{40}$/.test(row.revision)||seen.has(row.revision)||!Number.isFinite(time)||time<previous)throw Error('Invalid progress history');
      seen.add(row.revision);previous=time;
      for(const kind of fields){const m=row[kind];if(!m||!Number.isSafeInteger(m.total)||m.total<=0||!Number.isSafeInteger(m.linked)||m.linked<0||m.linked>m.total)throw Error('Invalid linked measurement');}
    }
    let count=Infinity;const users=new Set();
    for(const p of data.contributors){if(!/^[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,37}[a-zA-Z0-9])?$/.test(p.login)||users.has(p.login)||!Number.isSafeInteger(p.id)||p.id<=0||!Number.isSafeInteger(p.functions)||p.functions<=0||p.functions>count)throw Error('Invalid contributor credit');users.add(p.login);count=p.functions;}
  }
  scrub.addEventListener('input',()=>{if(rows.length){index=Number(scrub.value);draw();}});
  function point(event){
    if(!rows.length)return;const rect=chart.getBoundingClientRect(),fraction=Math.max(0,Math.min(1,(event.clientX-rect.left)/rect.width));
    const time=first+fraction*(last-first);index=rows.reduce((best,row,i)=>Math.abs(Date.parse(row.built_at)-time)<Math.abs(Date.parse(rows[best].built_at)-time)?i:best,0);draw();
  }
  chart.addEventListener('pointermove',point);
  chart.addEventListener('pointerdown',event=>{point(event);scrub.focus({preventScroll:true});});
  chart.addEventListener('pointerleave',()=>{if(rows.length){index=rows.length-1;draw();}});
  fetch('./activity.json',{cache:'no-cache'}).then(response=>{if(!response.ok)throw Error('Activity unavailable');return response.json();}).then(data=>{
    validate(data);rows=data.snapshots;index=rows.length-1;first=Date.parse(rows[0].built_at);last=Date.parse(rows[index].built_at);if(last===first)last=first+1;
    ceiling=Math.min(100,Math.max(5,Math.ceil(Math.max(...rows.flatMap(row=>fields.map(kind=>percent(row,kind))))/5)*5));
    scrub.max=rows.length-1;document.querySelector('.history-ceiling').textContent=ceiling+'%';
    const ticks=[first,(first+last)/2,last],format=last-first<3*86400000?fullDate:shortDate;
    document.querySelectorAll('.history-axis span').forEach((tick,i)=>tick.textContent=format.format(new Date(ticks[i])));
    renderPeople(data.contributors);draw();
  }).catch(()=>{document.querySelector('#history-date').textContent='Progress history unavailable';scrub.disabled=true;list.textContent='Contributor credits unavailable';});
})();
