console.clear();

const minuto = document.getElementById('display').childNodes[1];
const segundo = document.getElementById('display').childNodes[3];

const Timer = {
    seg : 0,
    min : 0,
    delay : null,
    flag : false,

    Start(){
        Timer.flag = true;
        Timer.delay = setInterval(()=>{

            segundo.innerText = String(Timer.seg++).padStart(2, '0');

            if(Timer.seg % 60 == 0) {
                Timer.seg = 0
                ++Timer.min
            }
            if(Timer.seg > 59) Timer.min = 0;
            minuto.innerText = String(Timer.min).padStart(2, '0');


        },1000);
    },

    Pause(){
        if(Timer.flag){
            clearInterval(Timer.delay);
            Timer.flag = false;
        }else{
            Timer.Start();
        }
    },

    Reset(){
        clearInterval(Timer.delay)
        minuto.innerText = '00'
        segundo.innerText = '00'
        Timer.seg = 0
        Timer.min = 0
        Timer.Start()
    },

};

Timer.Start()

minuto.onclick = ()=>{
    Timer.Pause();
}
segundo.onclick = ()=>{
    Timer.Reset();
}