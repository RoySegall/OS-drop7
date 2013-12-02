/**
 *
 */
(function ($, undefined) {

Drupal.behaviors.osLinkExternal = {
  attach: function (ctx) {
    $('#-os-link-external-form').submit(function (e) {
      if ($(this).filter(':visible').length > 0) {
        var value = $('#edit-external', this).val()
        // Trims the leading slash from the raw input value.
        Drupal.settings.osWysiwygLinkResult = value.replace(/^\//, "");
        Drupal.settings.osWysiwygLinkAttributes = {'data-url': Drupal.settings.osWysiwygLinkResult};
        e.preventDefault();
      }
    });
  }
};

Drupal.behaviors.osLinkInternal = {
  attach: function (ctx) {
    $('#-os-link-internal-form').submit(function (e) {
      // need to do something here to make sure we get a path and not a node title
      if ($(this).filter(':visible').length > 0) {
        Drupal.settings.osWysiwygLinkResult = $('#edit-internal', this).val();
        e.preventDefault();
      }
    });
  }
};

Drupal.behaviors.osLinkEmail = {
  attach: function (ctx) {
    $('#-os-link-email-form').submit(function (e) {
      if ($(this).filter(':visible').length > 0) {
        var val = $('#edit-email', this).val();
        if (val) {
          Drupal.settings.osWysiwygLinkResult = 'mailto:'+val;
        }
        else {
          Drupal.settings.osWysiwygLinkResult = '';
        }
        e.preventDefault();
      }
    });
  }
};

Drupal.behaviors.osLinkFile = {
  attach: function (ctx) {
    var params = Drupal.settings.media.browser.params;
    if (params) {
      if ('fid' in params) {
        $('div.media-item[data-fid="'+params.fid+'"]', ctx).click();
      }

      $('label[for="edit-filename"]', ctx).html('Search by Filename');

      $('#edit-file .form-actions input', ctx).click(function (e) {
        if ($(this).parents('#edit-file').filter(':visible').length > 0) {
          var selected = Drupal.media.browser.selectedMedia;
          if (selected.length) {
            var fid = selected[0].fid;

            Drupal.settings.osWysiwygLinkResult = selected[0].url;
            Drupal.settings.osWysiwygLinkAttributes = {"data-fid": fid};
          }
        }
      });
    }
  }
};

Drupal.behaviors.osLinkUpload = {
  attach: function (ctx, settings) {

    Drupal.ajax.prototype.commands.switchTab = function (ajax, response, settings) {
      jQuery('#'+response.tab).data('verticalTab').tabShow();
    };

    Drupal.ajax.prototype.commands.clickOn = function (ajax, response, settings) {
      jQuery(response.target).bind('click', Drupal.media.browser.views.click).click();
    }

    $('#file-entity-add-upload input[value="Next"]').addClass('use-ajax-submit');
    Drupal.behaviors.AJAX.attach(ctx, settings);
  }
};

Drupal.behaviors.osLinkTweaks = {
  attach: function (ctx, settings) {
    $('label[for="edit-upload-upload"]', ctx).each(function () {
      $(this).addClass('add-new').html('Add New');
    });
  }
};

})(jQuery, undefined);
