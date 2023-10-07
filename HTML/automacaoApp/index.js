window.onload = function() {
  
  if(localStorage.getItem("pageConfig") == null){
    // let pageConfig = ["SALA", "COZINHA", "QUARTO"];
    localStorage.setItem("pageConfig", []);//
    console.log('Salvo!')
  }else{
    let pageConfig = localStorage.getItem("pageConfig").split(',');
    console.log('Valor Guardado:',pageConfig);
  
    //cria os componentes
    
    pageConfig.forEach(element => {
      addButton(element);
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
}//toggleBtn

let componenteStruct = (itenName)=>{

  let itenId = document.getElementsByClassName('card').length; 
  
  return [`
  <div class="card">
  <div class="tools">
    <div class="circle">
      <span class="red box" onclick="removeIten(${ ++itenId })"></span>
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
          <input type="checkbox" id="${ itenId }" onclick="toggleBtn(this)">
          <span class="slider"></span>
        </label>
        <small>ID#${ itenId }</small>
        <h6>Ultima ação:</h6>
        <h6 id="log">Seg, 2 out 2023, 21:08:44</h6>

    </div>
  </div>
</div>`, itenId, itenName];

}//componenteStruct

function addButton(value){
  if(value != ''){
    value = value.toUpperCase()
    const page = componenteStruct(value);
    main.innerHTML += page[0];
    //console.log(page[1], page[2])
  }else{
    return
  }
}//addButton

function removeIten(id){
  console.log(`Removendo ID:${id}`);
}//removeIten

btnSave.onclick = ()=> {
  if(newName.value) {
    addButton(newName.value)
    let pageConfig = localStorage.getItem("pageConfig").split(',');
    pageConfig[pageConfig.length] = newName.value;
    
    console.log(pageConfig);
    
    localStorage.setItem("pageConfig", pageConfig);
  }
  newName.value = '';    
}//saveLocal