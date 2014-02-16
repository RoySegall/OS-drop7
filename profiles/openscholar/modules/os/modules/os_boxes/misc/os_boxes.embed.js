
(function ($) {

  Drupal.behaviors.osBoxesEmbedLinks = {
    attach: function (ctx) {
      $('.embed-popup').tabs().dialog({
        autoOpen: false,
        title: 'Share',
        height: 300,
        width: 500,
        modal: true
      });
      $('.os-embed-link').click(function (e) {
        var id = '#embed-popup-'+($(this).attr('data-delta'));
        $(id).dialog('open');
        e.preventDefault();
      });
    }
  }

})(jQuery);
