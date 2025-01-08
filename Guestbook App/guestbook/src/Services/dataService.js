export const fetchLocalData = async (filePath) => {
    try {
      const response = await fetch(filePath);
      if (!response.ok) {
        throw new Error('Network response was not ok');
      }
      return await response.json();
    } catch (error) {
      console.error('Fetch error:', error);
      throw error;
    }
  };

  export const fetchEmployeeData = async () => {
    try {
      const data = await fetchLocalData('/data/lookup.json');
      if (data && data.employees) {
        return data.employees;
      } else {
        throw new Error('Data format is incorrect');
      }
    } catch (error) {
      console.error('Error fetching data:', error);
      return [];
    }
  };

  export const fetchLocationData = async () => {
    try {
      const data = await fetchLocalData('/data/lookup.json');
      if (data && data.locations) {
        return data.locations;
      } else {
        throw new Error('Data format is incorrect');
      }
    } catch (error) {
      console.error('Error fetching data:', error);
      return [];
    }
  };

  export const fetchGuestData = async () => {
    try {
      const data = await fetchLocalData('/data/visitors.json');
      if (data && data.visitors) {
        return data.visitors;
      } else {
        throw new Error('Data format is incorrect');
      }
    } catch (error) {
      console.error('Error fetching data:', error);
      return [];
    }
  };

