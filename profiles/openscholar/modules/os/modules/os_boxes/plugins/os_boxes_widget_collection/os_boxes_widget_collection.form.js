
(function ($) {
Drupal.behaviors.tabs = {
  attach: function (ctx) {
    if ($('#widget-list', ctx).length == 0) return;	// do nothing if our table doesn't exist

    var $form = $('#boxes-add-form, #boxes-box-form'),
      template = '<tr class="draggable">'+$('input[name="widgets[widget-new][bid]"]', $form).parents('tr').hide().html()+'</tr>',
      tableDrag = Drupal.tableDrag['widget-list'],
      new_id = parseInt($('#edit-count').val());

    // add a new row to the table, set all its form elements to the right values and make it draggable
    $('.add-new', $form).click(function (e) {
      var bid = $('#edit-new', $form).val(),
        id, weight = -Infinity,
        new_row,
        count = $('#edit-count'),
        select = $('#edit-new').get(0),
        title = select.options[select.selectedIndex].innerHTML;

      count.val(parseInt(count.val())+1);
      id = 'widget-'+(new_id++);
      new_row = $(template.replace(/widget-new/g, id));

      // get the new weight
      $('.field-weight', $form).each(function () {
        if ($(this).val() > weight) {
          weight = parseInt($(this).val());
        }
      });
      // there are no existing form elements, start at 0.
      if (weight == -Infinity) {
        weight = 0;
      }

      // set all the form elements in the new row
      $('input[name="widgets['+id+'][bid]"]', new_row).val(bid);
      $('span', new_row).text(title);
      $('input[name="widgets['+id+'][title]"]', new_row).val(title);
      $('input[name="widgets['+id+'][weight]"]', new_row).addClass('field-weight').val(weight+1);
      $('.tabledrag-handle', new_row).remove();
      $('table tbody', $form).append(new_row);
      new_row = $('input[name="widgets['+id+'][bid]"]', $form).parents('tr');
      $('#edit-new', $form).val('');

      setup_remove(new_row);

      tableDrag.makeDraggable(new_row[0]);
      tableDrag.restripeTable();
    });

    // set up remove links.
    function setup_remove(ctx) {
      $('.remove', ctx).click(function () {
        var $this = $(this);
        $this.parents('tr').remove();
        tableDrag.restripeTable();

        // decrement counter
        var count = $('#edit-count');
        count.val(parseInt(count.val())-1);

        return false;
      });
    }

    setup_remove($form);
  }
};
})(jQuery);