$( document ).ready(function() {
    //alert( "ready!" );
    var elm1 = $('#input_1');
    alert('run');
    elm1.on('click', function () {
      //alert("Run");
      $('#1').text("SNPs for 1");
    });
    var elm2 = $('#input_2');
    elm2.on('click', function () {
      //alert("Run");
      $('#2').text("SNPs for 2");
    });
    var elm3 = $('#input_3');
    elm3.on('click', function () {
      //alert("Run");
      $('#3').text("SNPs for 3");
    });
    var elm4 = $('#input_4');
    elm4.on('click', function () {
      //alert("Run");
      $('#4').text("SNPs for 4");
    });
    //document.getElementById("1").innerHTML="SNPs for 1";
    //document.getElementById("2").innerHTML="SNPs for 2";
});
