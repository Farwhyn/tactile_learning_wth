// app.js
var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var SerialPort = require("serialport");
var port = new SerialPort("COM3");
var Readline = SerialPort.parsers.Readline;
var parser = new Readline();
var appdata;

app.use(express.static(__dirname + '/node_modules'));
app.get('/', function(req, res,next) {
    res.sendFile(__dirname + '/brain.html');
});

/* SERIAL WORK */

port.pipe(parser);
io.on('connection', function(client) {
    console.log('Client connected...');
    /*
    client.on('join', function(data) {
        //console.log(data);
        client.emit('serial_update', appdata);
    });
*/
   
});

/* SERIAL WORK */


parser.on('data', function(data) {
    console.log('data received: ' + data);
    io.emit('serial_update', data);
    appdata = data;
});

server.listen(4200);
