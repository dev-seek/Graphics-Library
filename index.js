const app = document.getElementById('app');
app.width = 800;
app.height = 600;
let ctx = app.getContext('2d');
let w = null

function make_env(...envs) {
	return new Proxy(envs , {
		get(target, prop,recevier) {
			for(let env of envs) {
				if(env.hasOwnProperty(prop)) {
					return env[prop];
				}
			}
			return (...args) => {console.error("NOT IMPLEMENTED : " +prop, args)}
		}
	});
}


WebAssembly.instantiateStreaming(fetch('./wasm.wasm'), {
	"env": make_env({
		"_Z6atan2fff": Math.atan2,
		"_Z4sinff": Math.sin,
		"_Z4cosff": Math.cos,
		"_Z5sqrtff": Math.sqrt,
	})
}).then(w0 => {
	w = w0;
		
	    // let prev = null;
		// function first(timestamp) {
			// prev = timestamp;
			// // console.log("first", timestamp);
			// window.requestAnimationFrame(loop);
		// }
		
		// function loop(timestamp) {
			// const delta = timestamp - prev;
			// prev = timestamp;

		// const pixels = w.instance.exports._Z6renderv(delta*0.001);
		const pixels = w.instance.exports._Z6renderv();

		const buffer = w.instance.exports.memory.buffer;
		// console.log("rotate", delta);
		const image = new ImageData( new Uint8ClampedArray(buffer, pixels, 800*600*4),app.width)
		ctx.putImageData(image, 0, 0);
	    // console.log(w);
		// update(context, BigInt(Math.floor(delta)));
		// window.requestAnimationFrame(loop);
	// }
	// window.requestAnimationFrame(first);
})



