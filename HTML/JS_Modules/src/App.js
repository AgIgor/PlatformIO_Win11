import { Notifyer } from './Notfier.js';
import { Timer } from './Timer.js';
import { Emitter } from './Emitter.js';


const App = {
     async start() {
        try{
        await Notifyer.init();
      }
      catch(err){
        console.log(err.message);
      }
     }
}

export { App };