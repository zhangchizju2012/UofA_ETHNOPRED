//Router for the ETHNOPRED
'use strict'

module.exports = function( app ) {

  var EP = app.Module[ 'EP' ];
  //var Helper = EP.helper;
  var Router = EP.router;
  var url = Router.dtree;
  var multipart = require( 'connect-multiparty' );
  var multipartMiddleware = multipart();

  app
    .post( url, multipartMiddleware, PostJSONDtree );

  app
    .get( url, GetJSONDTree );

  function GetJSONDTree () {
    console.log( 'running' );
  }

  function PostJSONDtree( req, res, next ) {
    var fs = require( 'fs' );
    console.log(req.files);
    var classifierType = req.body.classifierType;

    var filePath = req.files.file.path;

    console.log( filePath );
    console.log( classifierType );

    app.Waterfall([

    function readFile( callback ){
        
      var dataFolder = app.RootFolder + '/cpplib/cpp_code/tree_and_SNIP';
      var SNIPsuffix = '_SNIP';

      var fileMap = {
        Euro : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Euro' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Euro')
        },

        East_Asian  : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/East_Asian' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/East_Asian' )
        },

       Continent : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Continent' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Continent' )
        },

        American : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/American' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/American')
        },

       African : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/African' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/African' )
        }
      }

      var exec = require( 'child_process' ).exec;
      var classifier = fileMap[ classifierType ];

      if( classifier.type === 'country' ){
        
        //cmd_one is a 'country' based calculator
        var cmd = rootFolder + "/cpplib/ethnopred_once -i " + filePath;
        cmd += ' -T  ' + classifier.type;
        cmd += ' -s ' + classifier.SNIPFilePath;
        cmd += ' -t ' + classifier.TreeFilePath;

      } else if ( classifier.type === 'continent' ){
            
        //cmd_one is a 'country' based calculator
        var cmd = rootFolder + "/cpplib/ethnopred_twice -i " + filePath;

      } else {
      
      }
      
      console.log( rootFolder );
      console.log( cmd );

      exec( cmd, function( err, stdout, stderr ) {
        if( err ) {
            console.log( err );
            callback( true, "" );

        } else {
            var stdout = JSON.parse( stdout );
            callback( null, stdout );
        }
      });
    },

    ], function( err, results ) {
        if ( err ){
          if(debug){
            console.log( err );
          }
        } else {

          if( debug ){
            console.log( debug );
          }

          console.log(results);
          res.send( {data: results} );
          return next();
      }
    });
  }
}
