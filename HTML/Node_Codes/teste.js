const http = require('http');

// Create an instance of the http server to handle HTTP requests
let app = http.createServer((req, res) => {
    // Set a response type of plain text for the response
    res.writeHead(200, {'Content-Type': 'text/plain'});

    // Send back a response and end the connection
    res.end('Servidor NodeJs do Igor!\n');
});

// Start the server on port 3000
app.listen(5500, '192.168.15.150');
console.log('Node server running on port 5500');