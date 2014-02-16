/**
 * Starts up accordion widgets according to their settings
 */
(function ($) {
  Drupal.behaviors.osBoxesAccordion = {
    attach: function (ctx) {
      $.each(Drupal.settings.os_boxes.accordion, function (delta, data) {
        var $elem = $('#block-boxes-'+delta+' .accordion').accordion({
          collapsible: true,
          heightStyle: 'content',
          active: data.active
        })
      });
    }
  }
})(jQuery);
