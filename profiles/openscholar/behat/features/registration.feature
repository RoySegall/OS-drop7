Feature:
  Testing the event registration module.

  @api
  Scenario: Limit the registration capacity to 1 and verify it for a normal user.
    Given I am logging in as "john"
      And I turn on event registration on "Halley's Comet"
     When I visit "john/halleys-comet"
      And I set the event capacity to "1"
      And I fill in "Email" with "g@gmail.com"
      And I press "Signup"
      And I am not logged in
     When I am logging in as "michelle"
      And I visit "john/halleys-comet"
      And I should not see "Sign up for Halley's Comet"
     Then I delete "john" registration

  @api
  Scenario: Limit the registration capacity to 2 and verify it for a normal user.
    Given I am logging in as "john"
     When I visit "john/halleys-comet"
      And I set the event capacity to "2"
      And I fill in "Email" with "g@gmail.com"
      And I press "Signup"
      And I am not logged in
     When I am logging in as "michelle"
      And I visit "john/halleys-comet"
      And I should see "Sign up for Halley's Comet"
     Then I delete "john" registration
