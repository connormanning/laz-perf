var fs = require('fs');

fs.writeFileSync('combined.js',
        fs.readFileSync('build/emscripten/laz-perf.asm.js', { encoding: 'utf-8' }) +
        fs.readFileSync('app.js'));

