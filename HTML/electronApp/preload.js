const { contextBridge, ipcRenderer } = require('electron')

contextBridge.exposeInMainWorld('notfy', {
    alert: (btnId) => ipcRenderer.invoke('notfy:alert',btnId,'123'),
})


// window.addEventListener('DOMContentLoaded', () => {
//     const replaceText = (selector, text) => {
//       const element = document.getElementById(selector)
            
//       if (element) element.innerText = text
//     }
  
//     for (const type of ['chrome', 'node', 'electron']) {
//       replaceText(`${type}-version`, process.versions[type])
//     }
//   })