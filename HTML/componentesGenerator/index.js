console.clear();

let itenName = 'Luz da Cozinha'
let itenId = ()=> {return Math.floor(Math.random() * 100);}

let componenteStruct = (itenName)=>{
  thisId = itenId();
  return `
      <div class="componente">
        <h3>${itenName}</h3>
        <label class="switch">
          <input type="checkbox" id="${thisId}" onclick="toggleSwitch(this)">
          <span class="slider"></span>
        </label>
        <small>ID:#${thisId}</small>
      </div>`
}



// main.innerHTML += componenteStruct()
// main.innerHTML += componenteStruct()



function toggleSwitch(data){
  console.log(data.id, data.checked)
}

function addButton(value){
  if(value != ''){
    value = value.toUpperCase()
    main.innerHTML += componenteStruct(value)
    console.log(value)
    nameComponete.value = '';
  }else{
    return
  }
}

