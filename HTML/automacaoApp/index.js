window.onload = function() {
  
  if(localStorage.getItem("pageConfig") == null){
    let pageConfig = JSON.stringify({0:'Luz Sala', 1:'Luz Quarto', 2:'Luz Garagem'});
    // let pageConfig = JSON.stringify({});
    localStorage.setItem("pageConfig", pageConfig);//
    console.log('Salvo!')
  }else{
    let pageConfig = JSON.parse(localStorage.getItem("pageConfig"));
    console.log('Valor Guardado:',pageConfig);
    
    //cria os componentes
    
    Object.entries(pageConfig).forEach(([key, value]) => {
        // console.log(`${key} ${value}`);
        addButton(value, key); 
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

function toggleBtn(id){
  console.log(id.id, id.checked);
  let log = document.getElementById(`log${id.id}`);
  log.innerText = new Date().toString();
}//toggleBtn

let componenteStruct = (itenName, index)=>{

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
          <input type="checkbox" id="${ index }" onclick="toggleBtn(this)">
          <span class="slider"></span>
        </label>
        <small>ID#${ index }</small>
        <h6>Ultima ação:</h6>
        <h6 id="log${ index}"></h6>

    </div>
  </div>
</div>`;

}//componenteStruct

function addButton(value, index){
  if(value != ''){
    value = value.toUpperCase()
    const page = componenteStruct(value, index);
    main.innerHTML += page;
    //console.log(page[1], page[2])
  }else{
    return
  }
}//addButton

function removeIten(id, name){
  let pageConfig = JSON.parse(localStorage.getItem("pageConfig"));
  console.log('Removendo ID:',id,pageConfig[id]);
  
  if(confirm(`Remover ID: ${id} ${pageConfig[id]}`) == true){ 
    delete pageConfig[id];
    localStorage.setItem("pageConfig", JSON.stringify(pageConfig));
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