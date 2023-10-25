import { Timer } from './Timer.js';
import { Emitter } from './Emitter.js';


const App = {
    start() {
        console.log('Start');
        Timer.log();
        Emitter.on();
    }
}

export { App };