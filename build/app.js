/*
ETHNOPRED 0.1.0- 
https://github.com/solittlework/UofA_ETHNOPRED.git
Built on 2015-10-09
*/
'use strict'
module.exports = function( app ){
  var Module = app.Module[ 'EP.download' ];
  var Router = Module.router;
  var SNPRut = Router.SNP;
  var sampleRut = Router.sample;

  app
    .get( SNPRut, GetSNPFile );
  app
    .post( SNPRut, SendSNPFile );
  
  app
    .get( sampleRut, GetSampleFile );
  app
    .post( sampleRut, SendSampleFile );

  function GetSNPFile(){
    console.log( "Get SNP file" );
  }

  function GetSampleFile() {
    console.log( "Get sample file" );
    
  }

  function SendSNPFile( req, res, next ) {  
    console.log( req.body );
    var classifierType = req.body.classifierType;
    console.log( classifierType );
    var SNPFolder = app.RootFolder + '/public/SNP_file/SNP_list';

    var SNPFileMap = {
      'Continent' : 'Continent_149.csv',
      'Sub_continent' : 'Subcontinent_1488.csv',
      'Euro' : 'European_180.csv',
      'East_Asian' : 'EastAsian_606.csv',
      'American' : 'NorthAmerican_266.csv',
      'African' : 'African_553.csv',
      'Kenyann' : 'Kenyan_341.csv',
    }

    if ( typeof SNPFileMap[ classifierType ] === 'undefined' )
    {
      console.warn( ' [ERROR] cannot find classifier type ' ); 
    }

    var SNPFile = SNPFolder + '/' + SNPFileMap[ classifierType ];
    console.log( SNPFile );
    var fs = require( 'fs' );
    var stat = fs.statSync( SNPFile);
    var fileToSend = fs.readFileSync( SNPFile );
    res.set('Content-Type', 'text/csv');
    res.set('Content-Length', stat.size);
    res.set('Content-Disposition', SNPFile );
    console.log( fileToSend);
    res.send(fileToSend);
  }

  function SendSampleFile( req, res, next ) {
    var sampleFlieFolder = app.RootFolder + '/public/SNP_file/csv';
    var classifierType = req.body.classifierType;
    console.log( classifierType );

    var sampleFlieMap = {
      'Continent' : 'Continent.csv',
      'Sub_continent' : 'All.csv',
      'Euro' : 'European.csv',
      'East_Asian' : 'EastAsian.csv',
      'American' : 'NorthAmerican.csv',
      'African' : 'African.csv',
      'Kenyann' : 'Kenyan.csv',
    }

    if ( typeof sampleFlieMap[ classifierType ] === 'undefined' )
    {
      console.warn( ' [ERROR] cannot find classifier type ' ); 
    }

    var sampleFile = sampleFlieFolder + '/' + sampleFlieMap[ classifierType ];
    var fs = app.fs;
    var stat = fs.statSync( sampleFile );
    var fileToSend = fs.readFileSync( sampleFile );
    res.set( 'Content-Type', 'text/csv' );
    res.set( 'Content-Length', stat.size);
    res.set( 'Content-Disposition', sampleFile );
    res.send( fileToSend );
  }

}
;
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
