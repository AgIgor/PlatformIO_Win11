import { initializeApp } from 'https://www.gstatic.com/firebasejs/10.4.0/firebase-app.js'
import { getAnalytics } from 'https://www.gstatic.com/firebasejs/10.4.0/firebase-analytics.js'
import { 
            getAuth,
            createUserWithEmailAndPassword,
            signInWithEmailAndPassword,
            signOut
        } from 'https://www.gstatic.com/firebasejs/10.4.0/firebase-auth.js'
        
import { getFirestore } from 'https://www.gstatic.com/firebasejs/10.4.0/firebase-firestore.js'

const firebaseConfig = {
    apiKey: "AIzaSyDNzcnbwIxFIT4zQHpCTWNVEjMlcOyedAE",
    authDomain: "teste-b1ceb.firebaseapp.com",
    databaseURL: "https://teste-b1ceb-default-rtdb.firebaseio.com",
    projectId: "teste-b1ceb",
    storageBucket: "teste-b1ceb.appspot.com",
    messagingSenderId: "902399064152",
    appId: "1:902399064152:web:7a5f223380ba6a2b02f22d"
};

const firebase = initializeApp(firebaseConfig);
const auth = getAuth();


window.onload=()=>{
    console.log('ready');
    document.getElementById('app').innerHTML = `
            <input type="text" id="email" value='agigor@outlook.com'>
            <input type="password" id="pass" value='1207rogi'>
            <button id="entrar" >Entar</button>
            <button id="sair" >Sair</button>
            `
            
            entrar.addEventListener('click', () => {
                console.log('entrar');
                firebaseLogin(email.value, pass.value);
            });
            
            sair.addEventListener('click', () => {
                console.log('sair');
                firebaseLogout();
            });
};

function firebaseCreate(){
    createUserWithEmailAndPassword(auth, email, password)
      .then((userCredential) => {
        const user = userCredential.user;
        console.log(user);
      })
      .catch((error) => {
        const errorCode = error.code;
        const errorMessage = error.message;
        console.log(errorCode, errorMessage);
      });
};

function firebaseLogin(email, password) {
    signInWithEmailAndPassword(auth, email, password)
    .then((userCredential) => {
      const user = userCredential.user;
      console.log(user);
    })
    .catch((error) => {
      const errorCode = error.code;
      const errorMessage = error.message;
      console.log(errorCode,'\n', errorMessage);
    });
};

function firebaseLogout(){
    signOut(auth).then((e) => {
        console.log('logout');
      }).catch((error) => {
        console.log(error);
      });
};



