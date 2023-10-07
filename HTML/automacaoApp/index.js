

if(localStorage.getItem("theme") == 'dark'){
    switchTheme.checked = true;
    document.documentElement.style.setProperty("color-scheme", 'dark');
}else{
    switchTheme.checked = false;
    document.documentElement.style.setProperty("color-scheme", 'light');
}

function toggleTheme(t){
    
  if(t.checked){
    document.documentElement.style.setProperty("color-scheme", 'dark');
    localStorage.setItem("theme", "dark");
  }
  else{
    document.documentElement.style.setProperty("color-scheme", 'light');
    localStorage.setItem("theme", "light");
  }
}


function toggleBtn(id){
  console.log(id.id, id.checked);
}


let componenteStruct = (itenName)=>{

  let itenId = document.getElementsByClassName('card').length
  return [`
  <div class="card">
  <div class="tools">
    <div class="circle">
      <span class="red box"></span>
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
          <input type="checkbox" id="${ ++itenId }" onclick="toggleBtn(this)">
          <span class="slider"></span>
        </label>
        <small>ID#${ itenId }</small>
        <h6>Ultima ação:</h6>
        <h6 id="log">Seg, 2 out 2023, 21:08:44</h6>

    </div>
  </div>
</div>`, itenId, itenName];
}

function addButton(value){
  if(value != ''){
    value = value.toUpperCase()
    const page = componenteStruct(value);
    main.innerHTML += page[0];
    console.log(page[1], page[2])
    newName.value = '';
    
    //localStorage.setItem('pageConfig', JSON.stringify());
    let pageConfig = JSON;
    
    // const cards = document.getElementsByClassName('card');
    if(page[1] > 0){
      for (let i=0; i<page[1]; i++) {
        // console.log(cards[i])
        // console.log(pageConfig)
        //salvar um json com configs de ids e nomes dos componentes
      }
    }
    
  }else{
    return
  }
}