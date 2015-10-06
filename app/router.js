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