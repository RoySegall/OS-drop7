Feature:
  Testing the simple view widget.

  @api
  Scenario: Verify the simple view widget works after tagging node to term.
     Given I am logging in as "john"
      When I assign the node "First blog" with the type "blog" to the term "Stephen William Hawking"
       And I assign the node "First blog" with the type "blog" to the term "Air"
      When the widget "Simple view list" is set in the "Classes" page with the following <settings>:
        | authors                  | Stephen William Hawking  | select list |
        | science                  | Air                      | select list |
       And I visit "john/classes"
      Then I should see "First blog"

