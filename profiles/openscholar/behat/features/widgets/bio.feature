Feature:
  Testing the bio teaser widget.

  @api
  Scenario: Verify the bio teaser widget works fine.
     Given I am logging in as "john"
       And the widget "Bio" is set in the "Classes" page with the following <settings>:
           | Full Bio                   | edit-teaser-full  | radio     |
           | Display title of your Bio  | check             | checkbox  |
      When I visit "john/classes"
      Then I should see "John doe biography"
       And I should see "Work in gizra inc."
