Feature:
  Testing the viste access.

  @api
  Scenario: Testing the Vsite access to the views.
    Given I visit "news"
      And I should see "I opened a new personal"
      And I should see "Lou's site news"
      And I should see "More tests to the semester"
     When I visit "john/news"
     Then I should see "I opened a new personal"
      And I should see "More tests to the semester"
      And I should not see "Lou's site news"
     When I visit "als/news"
     Then I should not see "I opened a new personal"
      And I should not see "More tests to the semester"
      And I should see "Lou's site news"
