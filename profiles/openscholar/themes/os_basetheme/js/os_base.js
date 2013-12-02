document.createElement('header');
document.createElement('nav');
document.createElement('section');
document.createElement('article');
document.createElement('aside');
document.createElement('footer');
document.createElement('hgroup');
document.createElement('figure');


// Fixes tab behavior after using the skip link in IE or Chrome
Drupal.behaviors.osBase_skipLinkFocus = {
  attach: function (ctx) {
    var $ = jQuery,
        $skip = $('#skip-link a', ctx);
    
    $skip.click(function (e) {
      var target = $skip[0].hash.replace('#', '');

      setTimeout (function () {
        $('a[name="'+target+'"]').attr('tabindex', -1).focus();
      }, 100);
    });
  }
};


