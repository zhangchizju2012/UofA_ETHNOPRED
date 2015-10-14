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
    console.log( req.files );

    var reqData = req.body.data;
    var classifierType = JSON.parse( reqData ).classifierType;

    var filePath = req.files.file.path;

    console.log( filePath );
    console.log( classifierType );
    console.log( reqData );

    app.waterfall([

    function readFile( callback ){
        
      var dataFolder = app.RootFolder + '/public/SNP_file/tree_and_SNP'; 
      var binaryName = 'ethnopred_once';
      var binPath = app.RootFolder + '/public/SNP_bin/'
      var binaryFile = binPath + binaryName;
      var SNIPsuffix = '_SNIP';

      var fileMap = {
        Continent : {
          type : 'continent',
          SNIPFilePath : ( dataFolder + '/Sub' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub' )
        },

        Sub_continent : {
          type : 'subcontinent',
          SNIPFilePath : ( dataFolder + '/Sub' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub' )
        },

        Euro : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Sub_Euro' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub_Euro')
        },

        East_Asian  : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Sub_Asian' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub_Asian' )
        },

        American : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Sub_American' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub_American')
        },

       African : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Sub_African' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub_African' )
        },

        Kenyann : {
          type : 'country',
          SNIPFilePath : ( dataFolder + '/Sub_Kenyan' + SNIPsuffix ),
          TreeFilePath : ( dataFolder + '/Sub_Kenyan')
        }
      }

      var exec = require( 'child_process' ).exec;
      var classifier = fileMap[ classifierType ];
      if ( typeof classifier === 'undefined' ) {
        console.warning( '[ Error ]: Cannot find given classifier type' );
      }

      var cmd = binaryFile + ' -i ' + filePath;
      cmd += ' -T  ' + classifier.type;
      cmd += ' -s ' + classifier.SNIPFilePath;
      cmd += ' -t ' + classifier.TreeFilePath;

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
          if( app.DEBUG ){
            console.log( err );
          }
        } else {
          if( app.DEBUG ){
            console.log( results );
           
          }

          res.send( { data: results } );
          return next();
      }
    });
  }
}
