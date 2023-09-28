const firebaseConfig = {
    apiKey: "AIzaSyDNzcnbwIxFIT4zQHpCTWNVEjMlcOyedAE",
    authDomain: "teste-b1ceb.firebaseapp.com",
    databaseURL: "https://teste-b1ceb-default-rtdb.firebaseio.com",
    projectId: "teste-b1ceb",
    storageBucket: "teste-b1ceb.appspot.com",
    messagingSenderId: "902399064152",
    appId: "1:902399064152:web:7a5f223380ba6a2b02f22d"
};
  
firebase.initializeApp(firebaseConfig)
const dbBase = firebase.database()
   
// firebase.auth().signInWithEmailAndPassword('agigor@outlook.com', '1207rogi').then((e)=>{
//     console.log(e)
//   })
//   .catch(function(error) {
//     var errorCode = error.code;
//     var errorMessage = error.message;
//     console.log(errorCode);
//     console.log(errorMessage);
//   }); 

document.getElementById("data").innerText = Date()

function inicio(){
    btnOn.setAttribute('disabled', 'disabled');
    btnOff.setAttribute('disabled', 'disabled');
    
    Sair.setAttribute('disabled', 'disabled');
    Remover.setAttribute('disabled', 'disabled');
    Atual.setAttribute('disabled', 'disabled');
    Entrar.setAttribute('disabled', 'disabled');
    Criar.setAttribute('disabled', 'disabled');
    Atualizar.setAttribute('disabled', 'disabled');
    Recuperar.setAttribute('disabled', 'disabled');

}//end inicio

function btnCriar()
{
  
    let email = document.getElementById("inEmail").value//"teste@teste.com";
    let password = document.getElementById("inPass").value//"12345678";
      
    firebase.auth().createUserWithEmailAndPassword(email, password).then(() => {
        console.log("Salvo!")
    })
    .catch(function(error) {
      var errorCode = error.code;
      var errorMessage = error.message;
      console.log(errorCode);
      console.log(errorMessage);
    });  
}//end btn salvar
  
function btnAtualizar()
{
    const user = usuarioAtual();
    let nome = document.getElementById("inNome").value
      
    user.updateProfile({
        displayName: nome
    }).then(() => {
        console.log("Update successful")
        usuarioAtual();
    }).catch((error) => {
        console.log(error)
    }); 
}//end btn atualizar
  
function btnEntrar()
{
    let email = document.getElementById("inEmail").value//"teste@teste.com";
    let password = document.getElementById("inPass").value//"12345678";
      
    firebase.auth().signInWithEmailAndPassword(email, password).then(()=>{
      btnOn.removeAttribute('disabled');
      btnOff.removeAttribute('disabled');
      Sair.removeAttribute('disabled');
      getLedStatus();
      usuarioAtual(); 
    })
    .catch(function(error) {
      var errorCode = error.code;
      var errorMessage = error.message;
      console.log(errorCode);
      console.log(errorMessage);
    }); 
}//end btn entrar

function btnSair()
{
    firebase.auth().signOut().then(() =>{
      console.log("Saiu!")
      document.getElementById("userAtual").innerText = "Entre!"
      location.reload();
    })
    .catch(function(error) {
      var errorCode = error.code;
      var errorMessage = error.message;
      console.log(errorCode);
      console.log(errorMessage);
    });
}//end btn sair
  
function btnRemover()
{
    const user = usuarioAtual();
      
    user.delete().then(() => {
      console.log("Deletado!");
    }).catch((error) => {
      console.log(error);
    });
}//end btn remover
  
function usuarioAtual()
{
    let user = usuarioAtual();
    if (user !== null){ 
      console.log(`user ID: ${user.uid}`);
      console.log(`user email: ${user.email}`);
      console.log(`user nome: ${user.displayName}`);
      document.getElementById("userAtual").innerHTML = `NOME: ${user.displayName}<br> EMAIL: ${user.email}<br> UID: ${user.uid}`
      return user;
    }else{
      console.log("Sem usuario!")
      return "Sem usuario!"
    }
}//end btn usuarioAtual
  
function btnRecuperar()
{
  
}//end btn recuperar

inEmail.addEventListener("input",(e)=>{
    if(inEmail.value === "", inPass.value === ""){
        Entrar.setAttribute('disabled', 'disabled');
    }else{
        Entrar.removeAttribute('disabled');
    }
});
inPass.addEventListener("input",(e)=>{
    if(inPass.value === "", inEmail.value === ""){
        Entrar.setAttribute('disabled', 'disabled');
    }else{
        Entrar.removeAttribute('disabled');
    }
});

const btnOn = document.querySelector("#on");
const btnOff = document.querySelector("#off");

btnOn.onclick = ()=>  ledToggle(true)
btnOff.onclick = ()=> ledToggle(false)

function ledToggle(flag)
{
    dbBase.ref("/test/stream/data/ledPin2").set(flag)
    //     dbBase.ref("/test/stream/data/ledPin2").update({
    //         ledPin2: flag
    //   })
    .then(() => {
        console.log("Salvo!");
        getLedStatus();
    })
    .catch((error) => {
        console.error("Error: ", error);
    });
}
  
function getLedStatus()
{
    dbBase.ref("/test/stream/data/ledPin2").on('value', (snapshot) => {
        const data = snapshot.val()
        console.log(data)
    if(data){
        btnOn.setAttribute('style', 'background-color:#ccc;');
        btnOn.setAttribute('disabled', 'disabled');
        btnOff.removeAttribute('disabled');
        btnOff.setAttribute('style', 'background-color:red;');
    }
    else{
        btnOff.setAttribute('style', 'background-color:#ccc;');
        btnOff.setAttribute('disabled', 'disabled');
        btnOn.removeAttribute('disabled');
        btnOn.setAttribute('style', 'background-color:green;');
    
    }
    });
}

