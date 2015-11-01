'use strict'
module.exports = function( app ) {
  var Demo = app.Module[ 'EP.demo' ];
  var Router = Demo.router;
  var DemoUrl = Router.demo;

  app
    .get( DemoUrl, GetDemo );
  app
    .post( DemoUrl, PostDemo );

  function GetDemo() {
    console.log( "Welcome to Demo page" );
  }

  function PostDemo ( req, res, next ) {

    var reqData = req.body;
    console.log( 'Running' );
    console.log( reqData )
    var classifierType = reqData.classifierType;
    console.log( classifierType );

    var resMsg = {
      process : "EP Demo",
      err : "",
      data : ""
    }

    var dataFolder = app.RootFolder + '/public/SNP_file/tree_and_SNP';
    var binaryName = 'ethnopred_once';
    var binPath = app.RootFolder + '/public/SNP_bin/'
    var binaryFile = binPath + binaryName;
    var SNIPsuffix = '_SNIP';
    var sampleFlieFolder = app.RootFolder + '/public/SNP_file/csv';

    var sampleFlieMap = {
      'Continent' : 'Continent.csv',
      'Sub_continent' : 'All.csv',
      'Euro' : 'European.csv',
      'East_Asian' : 'EastAsian.csv',
      'American' : 'NorthAmerican.csv',
      'African' : 'African.csv',
      'Kenyan' : 'Kenyan.csv',
    }

    if ( typeof sampleFlieMap[ classifierType ] === 'undefined' )
    {
      console.warn( ' [ERROR] cannot find classifier type ' );
    }

    var sampleFile = sampleFlieFolder + '/' + sampleFlieMap[ classifierType ];

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
        SNIPFilePath : ( dataFolder + '/Sub_East_Asian' + SNIPsuffix ),
        TreeFilePath : ( dataFolder + '/Sub_East_Asian' )
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

      Kenyan : {
        type : 'country',
        SNIPFilePath : ( dataFolder + '/Sub_Kenyan' + SNIPsuffix ),
        TreeFilePath : ( dataFolder + '/Sub_Kenyan')
      }
    }

    var classifier = fileMap[ classifierType ];
    if ( typeof classifier === 'undefined' ) {
      console.warning( '[ Error ]: Cannot find given classifier type' );
    }

    var cmd = binaryFile + ' -i ' + sampleFile;
    cmd += ' -T  ' + classifier.type;
    cmd += ' -s ' + classifier.SNIPFilePath;
    cmd += ' -t ' + classifier.TreeFilePath;

    console.log( cmd );

    app.waterfall([
      function RunDemo( callback ) {
        var exec = require( 'child_process' ).exec;
        exec( cmd, function( err, stdout, stderr ) {
          if( err ) {
              console.log( err );
              callback( true, "" );

          } else {
              var stdout = JSON.parse( stdout );
              callback( null, stdout );
          }
        });
      }
    ],

    function( err, results ) {
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
    })
  }
}
