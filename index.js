// import the native addon using bindings
// const daqhats_module = require( './build/Release/daqhats-node.node' );
const daqhats_node = require('bindings')('daqhats-node');

// expose the module API
module.exports = daqhats_node;

// console.log( 'exports : ', mcc118_module); console.log();
// console.log( 'mcc118_module.setup       : ', mcc118_module.setup() ); console.log();
// console.log( 'mcc118_module.single_read : ', mcc118_module.single_read() ); console.log();
// console.log( 'mcc118_module.finalize    : ', mcc118_module.finalize() ); console.log();

