module.exports = function( app ){

	LoadPlugin( app );
	//LoadCustomerPlugin( app );
	LoadCommonLibaries( app );
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

	function LoadCommonLibaries ( app ) {

		app.waterfall = require( 'async' ).waterfall;
    console.log( 'Load waterfall func from async lib' ) 
    app.fs = require( 'fs' );
    console.log( 'Load fs func from fs lib' ); 
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
}
