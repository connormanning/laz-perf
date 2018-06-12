var o = new Module.LASZip();

let arraybuffer = require('fs').readFileSync('wide-color.laz');
var abInt = new Uint8Array(arraybuffer);
var buf = Module._malloc(arraybuffer.byteLength);

o.arraybuffer = arraybuffer;
o.buf = buf;
Module.HEAPU8.set(abInt, buf);
o.open(buf, arraybuffer.byteLength);

var pointsStructSize = 34;
var pointsToRead = 3;
var bufferSize = pointsToRead;
var pointsRead = 0;

let mybuffer = new ArrayBuffer(bufferSize * pointsStructSize);
let view = new DataView(mybuffer);
let this_buf = new Uint8Array(mybuffer);
var buf_read = Module._malloc(pointsStructSize);
var x, y, z, r, g, b;
for (var i = 0 ; i < pointsToRead; i ++) {
    o.getPoint(buf_read);
    var pos = i * pointsStructSize;

    var a = new Uint8Array(Module.HEAPU8.buffer, buf_read, pointsStructSize);
    this_buf.set(a, pointsRead * pointsStructSize, pointsStructSize);

    x = view.getInt32(pos + 0, true);
    y = view.getInt32(pos + 4, true);
    z = view.getInt32(pos + 8, true);

    r = view.getUint16(pos + 28, true);
    g = view.getUint16(pos + 30, true);
    b = view.getUint16(pos + 32, true);
    console.log('XYZ[' + i + ']', x, y, z);
    console.log('RGB[' + i + ']', r, g, b);
    console.log();

    ++pointsRead;
}
Module._free(buf_read);

