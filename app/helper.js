module.exports = function( app ) {
	var HelperMap = {
		'EP' : './ethnopred/helper.js'
	}

	app.Ext.LoadHelper( HelperMap );
}