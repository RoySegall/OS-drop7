(function ($) {

  Drupal.behaviors.osEventsSignupDescription = {

    attach: function () {
      var repeat = $('#edit-field-date-und-0-show-repeat-settings');
      var signup = $('#field-event-registration-add-more-wrapper');

      repeat.change(function() {
        if ($(this).is(':checked')) {
          signup.find('.description').text(Drupal.t('Only applicable to non repeated events.'));
        }
        else {
          signup.find('.description').text(Drupal.t('If checked, users will be able to signup for this event.'));
        }
      });
    }
  };

})(jQuery);

