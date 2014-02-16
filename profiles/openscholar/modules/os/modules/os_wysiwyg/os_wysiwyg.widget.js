/**
 * Adds behavior to self-hiding wysiwyg widget
 */
(function ($) {
  
  function wysiwyg_expand(e) {
    var parent;
    if (typeof e == 'undefined') { //wtf IE
      // only happens in IE when we click on the body element
      // IE doesn't pass an event object in when the event handler is assigned using onclick attribute
      e = this.document.parentWindow.event;
      e.currentTarget = e.srcElement;
      e.currentTarget.ownerDocument.defaultView = e.currentTarget.ownerDocument.parentWindow;
    }
    if (e.currentTarget.nodeName == 'BODY') {
      if (e.currentTarget.ownerDocument.defaultView.name.indexOf('_ifr') != -1) {
        parent = $('#'+e.currentTarget.ownerDocument.defaultView.name.replace('_ifr', '')).parents('.form-item');
      }
      else {
        var id = $(e.currentTarget).attr('onload').match(/'[\w\d-]+'/);
        id = id[0].slice(1, -1);
        parent = $('#'+id).parents('.form-item');
      }
    }
    else {
      parent = $(e.currentTarget).parents('.form-item');
    }
    var editor = parent.find('.mceEditor table.mceLayout'),
      height = (parseInt(parent.find('[data-maxrows]').attr('data-maxrows')) * 25);

    editor.removeClass('os-wysiwyg-collapsed');
    parent.find('.wysiwyg-toggle-wrapper').show();
    editor.stop().animate({height: height+'px'}, 600);
    $('iframe', editor).stop().animate({height: height+1+'px'}, 600);
    editor.children('tbody').children('tr.mceFirst, tr.mceLast').animate({opacity: 1.0}, 600);
  }

  function wysiwyg_minimize() {
    if (arguments.length) {
      var e = arguments[0],
        target = e.target || e.srcElement,
        target_id = $(target).parents('.mceEditor').find('table.mceLayout').attr('id');
    }
    $('.mceEditor table.mceLayout').not('.os-wysiwyg-collapsed').each(function () {
      var editor = $(this),
        parent = editor.parents('.form-item'),
        height = (parseInt(parent.find('[data-minrows]').attr('data-minrows')) * 20);

      if (this.id == target_id) {
        return;
      }

      // when a scrollable area is resized, it calculates the new scroll position with the following formula:
      // document.body.scrollTop = min(document.body.scrollTop, document.body.scrollHeight - window.innerHeight)
      // if the old scroll position was higher than the new maximum, it gets set to maximum
      // otherwise, nothing happens
      // we need to get the difference between old scroll position and new, subtract it from the height the wysiwyg tags,
      // and then subtract that from the new position


      editor.stop().animate({height: height+'px'}, 600)
        .addClass('os-wysiwyg-collapsed');
      $('iframe', editor).stop().animate({height: height+1+'px'}, 600);
      parent.find('.wysiwyg-toggle-wrapper').hide();
    })
  }

  function listboxClickHandler(e) {
    // there's no easy way to get the editor this list element is for. I have to muck about with the id string to
    // figure out which editor should be expanded.
    var id_frags = e.currentTarget.id.split('_'),
      dummy = {
        currentTarget: document.getElementById(id_frags[1])
      };

    wysiwyg_expand(dummy);
  }

  function bindHandlers(ctx) {
    $('.os-wysiwyg-expandable', ctx).each(function () {
      var edit_id = $(this).attr('id');
      if (typeof tinyMCE.editors[edit_id] !== 'undefined' && typeof tinyMCE.editors[edit_id].contentDocument !== 'undefined') {
        tinyMCE.editors[edit_id].contentDocument.getElementsByTagName('body')[0].onclick = wysiwyg_expand;
        $('#'+edit_id+'_tbl').click(wysiwyg_expand);
        // use mouseup because it fires before click, and can't be prevented by other scripts' click handlers
        $('body').mouseup(wysiwyg_minimize);

        wysiwyg_minimize();
        $('.os-wysiwyg-expandable ~ .wysiwyg-toggle-wrapper a').click(toggleHandlers);
      }
      else {
        setTimeout(function () { bindHandlers(ctx); }, 500);
      }
    });
  }

  function toggleHandlers(e) {
    bindHandlers($(this).parents('.text-format-wrapper'));
  }

  Drupal.behaviors.osWysiwygExpandingTextarea = {
    attach: function (ctx) {
      setTimeout(function () { bindHandlers(ctx); }, 500);
      if (typeof ctx.body != 'undefined') {
        $(ctx.body).delegate('.mceListBoxMenu[role="listbox"]', 'click', listboxClickHandler);
      }
    }
  };
})(jQuery);
