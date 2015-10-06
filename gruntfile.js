module.exports = function(grunt) {
  var banner = '/*\n<%= pkg.name %> <%= pkg.version %>';
  banner += '- <%= pkg.description %>\n<%= pkg.repository.url %>\n';
  banner += 'Built on <%= grunt.template.today("yyyy-mm-dd") %>\n*/\n';
  opt = {
    port: 3000
  };

  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    jshint: {
      options: {
        maxlen: 80,
        quotmark: 'single'
      },
      dev: ['app/**/*.js'],
    },

    karma: {
      unit: {
        configFile: 'karma.conf.js'
      }
    },

    express: {
      test: {
        options: {
          script: 'server.js',
          port: opt.port,
        }
      }
    },

    concat: {
      options: {
        separator: ';\n',
        banner: banner
      },

    build: {
      files: [{
        //Caution: load module folder by folder
        src: [ 'app/ethnopred/ethnopred.js' ], 
        dest: 'build/app.js'
        }]
      },
    },

    watch: {
      scripts: {
        files: [ 'app/ethnopred/ethnopred.js' ],
        tasks: ['concat'],
        options: {
              spawn: false,
        },
      }
    },

    uglify: {
      options: {
        banner: banner,
      },

      build: {
        files: { 
          'build/<%= pkg.name %>.min.js': 
            ['build/<%= pkg.name %>.js'],
        }
      }
    },

    mochaTest: {
      test: {
      options: {
        reporter: 'spec',
        captureFile: 'results.txt', // Optionally capture the reporter output to a file
        quiet: false, // Optionally suppress output to standard out (defaults to false)
        clearRequireCache: false // Optionally clear the require cache before running tests (defaults to false)
      },
        src: ['test/**/*.js']
      }
    },

    connect: {
      server: {
        options: {
            port: 8000,
            hostname: 'localhost'
        }
      }
    },

    execute: {
      target: {
        src: ['server.js']
      }
    },

    nodemon: {
        dev: {
          script: 'server.js'
        }
    },

    concurrent: {
      target: {
        tasks: ['nodemon', 'watch'],
        options: {
            logConcurrentOutput: true
        }
      }
    },

    forever: {
      server1: {
        options: {
          index: 'server.js',
          logDir: 'logs'
        }
      }
    }
  });

  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-express-server');
  grunt.loadNpmTasks('grunt-mocha-test');
  grunt.loadNpmTasks('grunt-karma');
  grunt.loadNpmTasks('grunt-contrib-connect');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-execute');
  grunt.loadNpmTasks('grunt-concurrent');
  grunt.loadNpmTasks('grunt-nodemon');
  grunt.loadNpmTasks('grunt-forever');
  grunt.registerTask('development', ['jshint', 'mocha']);
  grunt.registerTask('default', 
    ['jshint', 'mochaTest', 'concat', 'uglify', 'karma']);
  grunt.registerTask('test', ['express','mochaTest']);
  grunt.registerTask('start', ['concat', 'concurrent:target']);
  grunt.registerTask('startProduction', ['concat', 'forever:server1:restart'])
};