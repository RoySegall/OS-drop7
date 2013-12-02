(function ($) {

  Drupal.behaviors.os_reader = {
    attach: function (context, settings) {


      $('.feed-item-title').unbind('click').click(function() {
        $(this).parent().find('.feed-item-description').toggle();
      });


    }
  }
})(window.jQuery);
