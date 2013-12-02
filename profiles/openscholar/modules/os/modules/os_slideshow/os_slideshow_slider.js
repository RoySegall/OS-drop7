/**
 * @file os_slideshow_slider.js
 * 
 * Initializes responsive slides with each slideshow box's settings.
 */

(function ($) {

// Behavior to load responsiveslides
Drupal.behaviors.os_slideshow = {
  attach: function(context, settings) {
    $('body').once('os_slideshow', function() {

      var c = 0;
      for (var delta in Drupal.settings.os_slideshow) {      
        var $slider = $('div#' + delta).find('.rslides');
        if (c > 0) {
          Drupal.settings.os_slideshow[delta].namespace = delta;
        }
        c++;
        $slider.responsiveSlides(Drupal.settings.os_slideshow[delta]);
      }   
    });
    
   // Adds an exact height (from the ss image) to the .slide wrapper after the image is loaded and visible
    $(window).load(function() { 
      $img = $('.rslides img:first');
      $img.closest('div.slide').css('height', $img.height());
    });
  }
}


}(jQuery));
