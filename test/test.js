const assert = require('assert');
const addon  = require('..');

console.log( 'Test daqhats-node API' );

//const addon = require('./build/Release/daqhats-node');
// const addon = require('daqhats-node');

console.log('setup       : ',addon.setup());
console.log('single_read : ',addon.single_read());
console.log('finalize    : ',addon.finalize());


