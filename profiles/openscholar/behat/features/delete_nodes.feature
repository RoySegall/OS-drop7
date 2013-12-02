Feature: Testing the tagged items.
  Testing that two nodes tagged to one term and only one node tagged to another
  term.

  @api
  Scenario: verify that the tagged items filter work as expected.
      Given I am logging in as "admin"
        And I visit "john/classes"
        And I click "Add Class"
        And I fill in "Title" with "Dummy class"
        And I press "Save"
        And I click "Delete"
       When I press "Delete"
       Then I should verify i am at "john/classes"
