module.exports = function(grunt) {
  var banner = '/*\n<%= pkg.name %> <%= pkg.version %>';
  banner += '- <%= pkg.description %>\n<%= pkg.repository.url %>\n';
  banner += 'Built on <%= grunt.template.today("yyyy-mm-dd") %>\n*/\n';

  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    jshint: {
      options: {
        maxlen: 80,
        quotmark: 'single'
      },
      dev: ['gruntfile.js', 'app/*.js'],
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
            port: 3000,
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
          src: ['app/*.js'], 
          dest: 'build/<%= pkg.name %>.js'
        }]
      },
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
    watch: {
      scripts: {
        files: ['gruntfile.js', 'src/*.js', 'test/**/*.js'],
        tasks: ['development']
      }
    }
  });

  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-express-server');
  grunt.loadNpmTasks('grunt-mocha-test');
  grunt.loadNpmTasks('grunt-karma');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.registerTask('development', ['jshint', 'mocha']);
  grunt.registerTask('default', 
    ['jshint', 'mochaTest', 'concat', 'uglify', 'karma']);
  grunt.registerTask('test', 
    ['express','mochaTest']);
};
