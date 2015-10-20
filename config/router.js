module.exports = function( app ) {
	LoadModules( app );
  var RouterMap = {
    'EP' : {
      dtree : 'dtree.json'
    },

    'EP.download' : {
      SNP : 'download/SNP',
      sample: 'download/sample'
    },

    'EP.demo' : {
      demo : 'demo'
    }
  }

  LoadRouter( app, RouterMap );

  function LoadModules ( app ) {
    for ( var i = 0; i < app.Modules.length; i++ ){
      app.Ext.LoadModule( app.Modules[i], app );
      console.log( app.Modules[i] );
    }
  }
  
  function LoadRouter( app, RouterMap ){
    var Keys = Object.keys( RouterMap );
    for ( var i = 0; i < Keys.length; ++i ){
      var moduleRouter = RouterMap[ Keys[i] ];
      var RouterKeys = Object.keys( moduleRouter );
      for (var j = 0; j < RouterKeys.length; ++j ){
        moduleRouter[ RouterKeys[j] ] = app.RootRut + moduleRouter[ RouterKeys[j] ];
      }
      app.Module[ Keys[i] ].router = moduleRouter;
    }
  }
}
