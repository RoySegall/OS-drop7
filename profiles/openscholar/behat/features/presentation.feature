Feature:
  Testing the presentation tab.

  @api
  Scenario: Test the Persentation tab
    Given I visit "john"
     When I click "Presentations"
     Then I should see "JFK's biography"
