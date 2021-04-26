// Node modules
const getPixels = require("get-pixels");
const ndarray = require('ndarray');
const rgbHex = require('rgb-hex');
const cd = require('color-difference');
const request = require('request');

// Local vars
let ip = 'http://192.168.0.103';

start();

let started = false;
function start() {

  console.log("Looking for camera");

  startInterval = setInterval(() => {

    request.get(`${ip}/status`, async function (error, response, body) {
      if(!error && response.statusCode == 200) {
        started = true;
        console.log("Camera connected");
        clearInterval(startInterval);
        imageGetter();
      }
    });
    
  }, 200);

}

function imageGetter() {

  captureInterval = setInterval(() => {

        getPixels(`${ip}/capture`, function(err, pixels){
          console.log("Captured image");
          if (err){
            console.log(err);
            return;
          } else {

            console.log("Analyzing image");
        
            var w = 320;
            var h = 240;
        
            var l = w * h;
            let xs = [];
            for (var i = 0; i < l; i++) {
                // get color of pixel
                var r = pixels.data[i*4]; // Red
                var g = pixels.data[i*4+1]; // Green
                var b = pixels.data[i*4+2]; // Blue
                var a = pixels.data[i*4+3]; // Alpha
        
                // get the position of pixel
                var y = parseInt(i / w, 10);
                var x = i - y * w;
        
                let hex = rgbHex(r, g, b);
                let compare = cd.compare('#'+hex, '#27497d');
                if(compare < 5) xs.push(x);
            }
            if(xs[0] < 140) requestRover('left');
            if(xs[0] > 160) requestRover('right');
            if(xs[0] < 140 && xs[0] > 160) requestRover('forward');
            if(xs.length == 0) requestRover('ignore');
          }
        });
    
  }, 5000);

}

function requestRover(uri) {

  request.get(`${ip}/uri`, async function (error, response, body) {
    if(!error && response.statusCode == 200) {
      console.log("Requested rover: "+uri);
    }
  });

}