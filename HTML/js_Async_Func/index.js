console.log('inicio');

const delay =  setInterval(async()=>{

    try{
        await console.low('delay'); 
    }
    catch(err){
        console.log(err)
    }
    
    
},3000);