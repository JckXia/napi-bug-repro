{
  "targets": [
    {
      "target_name": "binding",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "electron_thread.cc"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
       'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
       "cflags!" : [],
       
    "configurations": {
        # This is used for generating code coverage with the `--debug` argument
        "Debug": {
          "conditions": [
            ['OS=="linux"', {
              "cflags": [],
              "ldflags": []
            }],
            ['OS=="mac"', {
              "xcode_settings": {
                "OTHER_CFLAGS": [
                  "-fprofile-arcs -ftest-coverage",
                ],
                "OTHER_LDFLAGS": [
                ]
              }
            }]

          ]
        },
    }
    },
    
  ]
}
