const { app, Notification ,  BrowserWindow, ipcMain } = require('electron')
const path = require('node:path')

function createWindow () {
  const win = new BrowserWindow({
    width: 600,
    height: 400,
    resizable: false,
    fullscreenable : false,
    frame : true,
    alwaysOnTop : false,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    }
  })

  win.loadFile('index.html')
}

const NOTIFICATION_TITLE = 'Basic Notification'
const NOTIFICATION_BODY = 'Notification from the Main process'

function showNotification (t) {
    new Notification({ title: t, body: NOTIFICATION_BODY }).show()
}

ipcMain.handle('notfy:alert', (obj, btnId, value) => {

    showNotification(btnId);
    return `${btnId}, ${value}`
    
})

app.whenReady().then(createWindow)//.then(showNotification)

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit()
    }
})
  
app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow()
    }
})