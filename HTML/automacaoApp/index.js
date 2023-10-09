window.onload = function() {
  
  if(localStorage.getItem("pageConfig") == null){
    // let pageConfig = JSON.stringify({0:'Luz Sala', 1:'Luz Quarto', 2:'Luz Garagem'});
    let pageConfig = JSON.stringify({});
    let logJson = JSON.stringify({});
    localStorage.setItem("pageConfig", pageConfig);//
    localStorage.setItem("logJson", logJson);//
    console.log('Salvo!')
  }else{
    let pageConfig = JSON.parse(localStorage.getItem("pageConfig"));
    let logJson = JSON.parse(localStorage.getItem("logJson"));
    console.log('Valor Guardado:',pageConfig,'\n', logJson);
    
    //cria os componentes
    
    Object.entries(pageConfig).forEach(([key, value]) => {
        // console.log(`${key} ${value}`);
        addButton(value, key, logJson[key]);
    });
     
  }

  if(localStorage.getItem("theme") == 'dark'){
    switchTheme.checked = true;
    document.documentElement.style.setProperty("color-scheme", 'dark');
  }else{
    switchTheme.checked = false;
    document.documentElement.style.setProperty("color-scheme", 'light');
  }
  
}//end window onload

function toggleTheme(t){
    
  if(t.checked){
    document.documentElement.style.setProperty("color-scheme", 'dark');
    localStorage.setItem("theme", "dark");
  }
  else{
    document.documentElement.style.setProperty("color-scheme", 'light');
    localStorage.setItem("theme", "light");
  }
}//toggleTheme

function toggleBtn(id,name){
// console.clear()

  let log = document.getElementById(`log${id.id}`);
  var meses = [
    "Jan",
    "Fev",
    "Mar",
    "Abr",
    "Mai",
    "Jun",
    "Jul",
    "Ago",
    "Set",
    "Out",
    "Nov",
    "Dez"
  ];
  var days = ['Dom','Seg','Ter','Qua','Qui','Sex','Sáb'];
  let d = new Date();
  console.log(days[d.getUTCDay()],d.getUTCDate(),meses[d.getMonth()],d.getFullYear());
  
  let logStr = `${days[d.getUTCDay()]} ${d.getUTCDate()} ${meses[d.getMonth()]} ${d.getFullYear()} ${d.getHours()}:${d.getMinutes()}`
  
  // logStr = logStr.replace('GMT-0300 (Horário Padrão de Brasília)', '');
  
  log.innerText = logStr;
  // console.log(id.id, id.checked, name, logStr);
  
  let logJson = JSON.parse(localStorage.getItem("logJson"));
  logJson[id.id] = logStr;
  localStorage.setItem("logJson", JSON.stringify(logJson));

}//toggleBtn

let componenteStruct = (itenName, index, logJson)=>{

  let itenId = document.getElementsByClassName('card').length; 
  
  return `
  <div class="card">
  <div class="tools">
    <div class="circle">
      <span class="red box" onclick="removeIten(${ index},'${ itenName }')"></span>
    </div>
    <div class="circle">
      <span class="yellow box"></span>
    </div>
    <div class="circle">
      <span class="green box"></span>
    </div>
  </div>
  <div class="card__content">
    <div class="device">
        <h2>${ itenName }</h2>
        <label class="switch">
          <input type="checkbox" id="${ index }" onclick="toggleBtn(this,'${ itenName }')">
          <span class="slider"></span>
        </label>
        <small>ID#${ index }</small>
        <h6>Ultima ação:</h6>
        <h6 id="log${ index}">${logJson}</h6>

    </div>
  </div>
</div>`;

}//componenteStruct

function addButton(value, index, logJson){
  if(value != ''){
    value = value.toUpperCase()
    logJson = (logJson  === undefined ? 'Sem Dados!': logJson);
    const page = componenteStruct(value, index, logJson);
    main.innerHTML += page;
    
    let lJson = JSON.parse(localStorage.getItem("logJson"));
    lJson[index] = logJson;
    localStorage.setItem("logJson", JSON.stringify(lJson));
  }else{
    return
  }
}//addButton

function removeIten(id, name){
  let pageConfig = JSON.parse(localStorage.getItem("pageConfig"));
  let logJson = JSON.parse(localStorage.getItem("logJson"));
  console.log('Removendo ID:',id,pageConfig[id]);
  
  if(confirm(`Remover ID: ${id} ${pageConfig[id]}`) == true){ 
    delete pageConfig[id];
    delete logJson[id];
    localStorage.setItem("pageConfig", JSON.stringify(pageConfig));
    localStorage.setItem("logJson", JSON.stringify(logJson));
    location.reload();
  }
  else{
    return
  }
 
}//removeIten

btnSave.onclick = ()=> {
  if(newName.value) {
    let pageConfig = JSON.parse(localStorage.getItem("pageConfig"));
    let tamanho = Object.entries(pageConfig).length
    pageConfig[++tamanho] = newName.value.toUpperCase();
    console.log(pageConfig)
    
    // Object.entries(arr).forEach(([k,v])=> {
    //   console.log(k,v)
    // })
    localStorage.setItem("pageConfig", JSON.stringify(pageConfig));
    addButton(newName.value, tamanho)
    
  }
  newName.value = '';    
}//saveLocal

newName.onkeypress = function(event) {
  if (event.key === "Enter") {
    event.preventDefault();
    document.getElementById("btnSave").click();
  }
}