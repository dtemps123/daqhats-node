{
  "targets": [
    {
      "target_name": "daqhats-node",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
	"./src/daqhats_utils.c",
        "./src/mcc118_single_read.c",
        "./src/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      "libraries": [
	"/usr/local/lib/libdaqhats.so.1.4.0.3"
      ]
    }
  ]
}
