import React from 'react';
import { useLocation } from 'react-router-dom';
import NewVisNav from '../Components/NewVisNav';
import GuestFill from '../Components/GuestFilling';

export function CheckIn() {
  const location = useLocation();
  const formData = location.state?.formData || {};

  return (
    <div className="Home">
      <nav>
        <NewVisNav />
      </nav>
      <main>
        <GuestFill formData={formData} />
      </main>
    </div>
  );
}

export default CheckIn;
