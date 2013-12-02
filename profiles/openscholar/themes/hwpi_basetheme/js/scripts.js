(function ($) {
  Drupal.behaviors.hwpiRemoveStuff = {
    attach: function(context) {
      $('ul.ui-tabs-nav').removeClass('ui-helper-clearfix');
      //$('ul.ui-tabs-nav li a').wrapInner('<span>');
    }
  };

  Drupal.behaviors.hwpiMenuToggle = {
    attach: function (ctx) {
      if ($('.mobile-buttons', ctx).length == 0) return;

      $('.mobile-buttons a[data-target]').each(function () {
          var $this = $(this),
              $pop = $($this.attr('data-target'));

          if ($pop.length == 0) {
            $this.remove();
          }
        }
      )

      $('.mobile-buttons a[data-target]').click(function (e) {
          var $this = $(this),
              $pop = $($this.attr('data-target'));
          if (!$pop.hasClass('opened')) {
            $('.toggled').removeClass('toggled');
            $this.addClass('toggled');
            $('.opened').removeClass('opened');
            $pop.addClass('opened');
          }
        else {
            $('.opened').removeClass('opened');
            $('.toggled').removeClass('toggled');
          }
        }
      );
    }
  }
})(jQuery);
