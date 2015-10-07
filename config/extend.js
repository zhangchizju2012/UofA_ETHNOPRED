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
    var baseFolder = app.RootFolder + '/app/';
		for( var i = 0; i < Keys.length; ++i ){
			app.Module[ Keys[i] ].helper 
				= require( baseFolder +  HelperMap[ Keys[i] ] );
		}
	}

	app.Ext.extend = require( 'extend' );

}
