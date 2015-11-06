/*
ETHNOPRED 0.1.0- 
https://github.com/solittlework/UofA_ETHNOPRED.git
Built on 2015-11-06
*/
module.exports = function( app ){

	LoadPlugin( app );
	//LoadCustomerPlugin( app );
	LoadGlobalAsync( app );
	LoadGolbalMessage( app );

	ConfigViewEngine( app );
	ConfigDomain( app );
	ConfigPort( app );
	ConfigDebugMode( app );
	//ConfigMySql( app );

	function LoadPlugin( app ) {

		var pluginArr = [
			'body-parser', 
			'express-validator'
		];

		for ( var i = 0; i < pluginArr.length; i++ ){
			app.use( require( pluginArr[i])() );
		}
	}

	function ConfigViewEngine( app ) {
		var path = require( 'path' );
		/*Set EJS template Engine*/
		app.set( 'view engine','ejs' );
	}

	function ConfigDomain( app ) {
		app.use( CrossAllDomain );
	}

	function CrossAllDomain( req, res, next ){
		res.header('Access-Control-Allow-Origin', '*');
	    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,OPTIONS');
	    res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization, Content-Length, X-Requested-With');

	    // intercept OPTIONS method
	    if ('OPTIONS' == req.method) {
	        res.send( 200 );
	    } else {
		    next();
	    }
	}

	function ConfigMySql( app ){
		var connection  = require( 'express-myconnection' );
	    var mysql = require( 'mysql' );

	    var MysqlOptions = {
	        host     : 'localhost',
	        user     : 'pssp_idm',
	        password : 'pssp_idm',
	        database : 'idm_db_test',
	        debug    : false //set true if you wanna see debug logger
	    }

		app
			.use( connection( mysql,
				MysqlOptions,
			    'pool' )
			);
	}

	function LoadCustomerPlugin ( app ) {
		app.SQLQuery = require('../custom_lib/js/mysql_query.js');
	}

	function ConfigPort( app ) {
		app.Port = process.env.PORT || 3001;
	}

	function LoadGlobalAsync ( app ) {

		app.Waterfall = require( 'async' ).waterfall;

	}

	function ConfigDebugMode( app ){
		app.DEBUG = true;
	}

	function LoadGolbalMessage( app ){
		app.MSG = {
			DB_CONN_SUCCESS: 
				'[ DATABASE ] SUCCESSFULLY CONNECTED TO DATABASE',

			DB_CONN_FAIL: 
				'[ DATABASE ] ERROR: CANNOT CONNECT TO DATABASE',				
			PrintDBData: 
				function( data ){
				console.log ( '[ DATABASE ] SUCCESSFULLY EXTRACTED DATA FROM DATABASE' );
				console.log( 'THE CONTENT IS');
				console.log( data );
			}
		}

	}
};
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
    var sampleFlieFolder = app.RootFolder + '/public/sample';

    var sampleFlieMap = {
      'Continent' : 'Sample_file_for_Continent_CEU-CHB-JPT-YRI_149.csv',
      'Sub_continent' : 'All.csv',
      'Euro' : 'Sample_file_for_Subcontinent-European_CEU-TSI_180.csv',
      'East_Asian' : 'Sample_file_for_Subcontinent-East-Asian_CHB-JPT_606.csv',
      'American' : 'Sample_file_for_Subcontinent_North-american_ASW-CEU-CHD-GIH-MXL_266.csv',
      'African' : 'Sample_file_for_Subcontinent_African-LWK-MKK-YRI_553.csv',
      'Kenyan' : 'Sample_file_for_Subcontinent_Kenyan-LWK-MKK_341.csv'
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
              console.log( stdout );
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
;
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
      'Kenyan' : 'Kenyan_341.csv',
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
    var sampleFlieFolder = app.RootFolder + '/public/sample';
    var classifierType = req.body.classifierType;
    console.log( classifierType );

    var sampleFlieMap = {
      'Continent' : 'Sample_file_for_Continent_CEU-CHB-JPT-YRI_149.csv',
      'Sub_continent' : 'All.csv',
      'Euro' : 'Sample_file_for_Subcontinent-European_CEU-TSI_180.csv',
      'East_Asian' : 'Sample_file_for_Subcontinent-East-Asian_CHB-JPT_606.csv',
      'American' : 'Sample_file_for_Subcontinent_North-american_ASW-CEU-CHD-GIH-MXL_266.csv',
      'African' : 'Sample_file_for_Subcontinent_African-LWK-MKK-YRI_553.csv',
      'Kenyan' : 'Sample_file_for_Subcontinent_Kenyan-LWK-MKK_341.csv'
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
;
'use strict'
module.exports = {};
'use strict'
module.exports = function( app ){

	if ( typeof app.Ext === 'undefined' ){
		app.Ext = {};
	}

	app.Ext.LoadModule = function( ModuleName ){

		if ( typeof app.Module == 'undefined' ){
			app.Module = {};
		}

		if ( app.Modules.lastIndexOf( ModuleName ) === -1 ){

			console.warn( 'Module ' + ModuleName + 'has not been registered' );

		} else {

			if ( typeof app.Module[ ModuleName ] === 'undefined' ){
				app.Module[ ModuleName ] = {};
				app.Module[ ModuleName ][ 'helper' ] = {};
				app.Module[ ModuleName ][ 'router' ] = {};
			}
		}
	}

	app.Ext.LoadHelper = function ( HelperMap ) {
		var Keys = Object.keys( HelperMap );
		for( var i = 0; i < Keys.length; ++i ){
			app.Module[ Keys[i] ].helper 
				= require( HelperMap[ Keys[i] ] );
		}
	}

	app.Ext.extend = require( 'extend' );

};
module.exports = function( app ) {
	var HelperMap = {
		'EP' : './ethnopred/helper.js'
	}

	app.Ext.LoadHelper( HelperMap );
};
module.exports = function( app ) {
	LoadModules( app );

	app.Module[ 'EP' ].router = {
		dtree : app.RootRut + 'dtree.json'
	}

	function LoadModules ( app ) {
		for ( var i = 0; i < app.Modules.length; i++ ){
			app.Ext.LoadModule( app.Modules[i], app );
			console.log( app.Modules[i] );
		}
	}
}