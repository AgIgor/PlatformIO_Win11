window.onload = () => {
    console.log('onload');
}


document.addEventListener('keypress',(key)=>{
    console.log(key.key, key.code);
})